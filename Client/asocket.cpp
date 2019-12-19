#include "asocket.h"
#include <WinSock2.h>

ASocket::ASocket() : 
	PB::socket(::WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)),
	_completionReadThread(NULL),
	_completionWriteThread(NULL)
{
	HANDLE completionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(completionPort == 0)
		throw std::runtime_error("cannot create completion port");

	this->_completionReadThread = new std::thread(&ASocket::completionReadThreadRoutine, this, INVALID_HANDLE_VALUE);
	this->_completionWriteThread = new std::thread(&ASocket::completionWriteThreadRoutine, this, INVALID_HANDLE_VALUE);
}

ASocket::~ASocket()
{
	if(this->_completionReadThread)
	{
		this->_completionReadThread->join();
		delete this->_completionReadThread;
	}

	if(this->_completionWriteThread)
	{
		this->_completionWriteThread->join();
		delete this->_completionWriteThread;
	}
}

bool ASocket::connect(const std::string& ip, uint16_t port)
{
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);

	if (addr.sin_addr.s_addr == -1)
	{
		struct hostent* entry = ::gethostbyname(ip.c_str());
		if (entry == NULL)
			return false;

		addr.sin_addr.s_addr = *((unsigned long *)(entry->h_addr_list[0]));
	}

	if(::WSAConnect(this->_fd, (struct sockaddr*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR && WSAGetLastError() != EWOULDBLOCK)
		return false;

	return true;
}

void ASocket::completionReadThreadRoutine(HANDLE completionPort)
{
	DWORD  dwBytesTransferred;
	LPPER_HANDLE_DATA handleData;
	LPPER_IO_DATA     ioData;
	DWORD  dwFlags;

	while( TRUE )
	{
		// 5. ��.����� �Ϸ�� ������ ���� ����
		GetQueuedCompletionStatus( completionPort,		// Completion Port
			&dwBytesTransferred,						// ���۵� ����Ʈ ��
			(LPDWORD) &handleData,
			(LPOVERLAPPED *) &ioData,
			INFINITE
		);

		if( dwBytesTransferred == 0 )		// EOF ���� ��
		{
			closesocket( handleData->fd );

			delete handleData;
			delete ioData;

			continue;
		}

		// ���ۿ� ����
		this->_istream.insert(this->_istream.end(), ioData->buffer, ioData->buffer + dwBytesTransferred);


		// �ٽ� �񵿱� ����
		memset( &(ioData->overlapped), 0, sizeof( OVERLAPPED ) );
		ioData->wsaBuf.len = sizeof(ioData->buffer);
		ioData->wsaBuf.buf = ioData->buffer;

		dwFlags = 0;
		WSARecv( handleData->fd,
			&(ioData->wsaBuf),
			1,
			NULL,
			&dwFlags,
			&(ioData->overlapped),
			NULL
		);
	}
}

void ASocket::completionWriteThreadRoutine(HANDLE completionPort)
{
	DWORD  dwBytesTransferred;
	LPPER_HANDLE_DATA handleData;
	LPPER_IO_DATA     ioData;
	DWORD  dwFlags;

	while( TRUE )
	{
		// 5. ��.����� �Ϸ�� ������ ���� ����
		GetQueuedCompletionStatus( completionPort,		// Completion Port
			&dwBytesTransferred,						// ���۵� ����Ʈ ��
			(LPDWORD) &handleData,
			(LPOVERLAPPED *) &ioData,
			INFINITE
		);

		if( dwBytesTransferred == 0 )		// EOF ���� ��
		{
			closesocket( handleData->fd );

			delete handleData;
			delete ioData;

			continue;
		}

		// �۽� �Ϸ�� �����ʹ� ����
		this->_ostream.erase(this->_ostream.begin(), this->_ostream.begin() + dwBytesTransferred);
		if(this->_ostream.size() == 0)
			continue;

		memcpy(ioData->buffer, this->_ostream.data(), min(this->_ostream.size(), sizeof(ioData->buffer)));


		// �ٽ� �񵿱� ����
		memset( &(ioData->overlapped), 0, sizeof( OVERLAPPED ) );
		ioData->wsaBuf.len = sizeof(ioData->buffer);
		ioData->wsaBuf.buf = ioData->buffer;

		dwFlags = 0;
		WSASend( handleData->fd,
			&(ioData->wsaBuf),
			1,
			NULL,
			dwFlags,
			&(ioData->overlapped),
			NULL
		);
	}
}
