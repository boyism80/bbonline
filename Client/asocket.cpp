#include "asocket.h"
#include <WinSock2.h>

ASocket::ASocket() : 
	PB::socket(::WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)),
	_completionReadThread(NULL),
	_completionWriteThread(NULL),
	_completionPort(INVALID_HANDLE_VALUE)
{
	this->_completionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(this->_completionPort == 0)
		throw std::runtime_error("cannot create completion port");

	this->_completionReadThread = new std::thread(&ASocket::completionReadThreadRoutine, this, this->_completionPort);
	this->_completionWriteThread = new std::thread(&ASocket::completionWriteThreadRoutine, this, this->_completionPort);
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
	//u_long opt = 0;
	//::ioctlsocket(this->_fd, FIONBIO, &opt);

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

	if(::WSAConnect(this->_fd, (struct sockaddr*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		return false;

	//opt = 1;
	//::ioctlsocket(this->_fd, FIONBIO, &opt);

	PER_HANDLE_DATA* handleData = new PER_HANDLE_DATA;
	handleData->fd = this->_fd;
	memcpy(&(handleData->addr), &addr, sizeof(addr));
	CreateIoCompletionPort((HANDLE)this->_fd, this->_completionPort, (DWORD) handleData, 0);

	PER_IO_DATA* ioData = new PER_IO_DATA;
	memset( &(ioData->overlapped), 0, sizeof( OVERLAPPED ) );
	ioData->wsaBuf.len = sizeof(ioData->buffer);
	ioData->wsaBuf.buf = ioData->buffer;


	DWORD dwFlags = 0;
	WSARecv(this->_fd, &(ioData->wsaBuf), 1, NULL, &dwFlags, &(ioData->overlapped), NULL);
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
		// 5. 입.출력이 완료된 소켓의 정보 얻음
		bool result = GetQueuedCompletionStatus(completionPort, &dwBytesTransferred, (LPDWORD) &handleData, (LPOVERLAPPED *) &ioData, INFINITE);
		int err = ::GetLastError();

		if( dwBytesTransferred == 0 )		// EOF 전송 시
		{
			closesocket( handleData->fd );

			delete handleData;
			delete ioData;

			continue;
		}

		// 버퍼에 저장
		this->_istream.insert(this->_istream.end(), ioData->buffer, ioData->buffer + dwBytesTransferred);
		this->handle_receive();


		// 다시 비동기 수신
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
	LPPER_HANDLE_DATA handleData;
	LPPER_IO_DATA     ioData;
	DWORD  dwFlags;

	while( TRUE )
	{
		if(this->_ostream.size() == 0)
			continue;

		int sent = ::send(this->_fd, (const char*)this->_ostream.data(), this->_ostream.size(), 0);
		int err = WSAGetLastError();
		if(sent == SOCKET_ERROR && err != WSAEWOULDBLOCK)
			continue;

		if(sent == 0)
			break;

		// 송신 완료된 데이터는 제거
		this->_ostream.erase(this->_ostream.begin(), this->_ostream.begin() + sent);
	}
}
