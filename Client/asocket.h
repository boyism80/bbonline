#ifndef __ASOCKET_H__
#define	__ASOCKET_H__

#include "PBSocket.h"
#include <string>
#include <thread>
#include <stdexcept>

using namespace PB;

typedef struct			// 소켓 정보를 구조체화
{
	SOCKET      fd;
	SOCKADDR_IN addr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct			// 소켓의 버퍼 정보를 구조체화
{
	OVERLAPPED overlapped;
	CHAR       buffer[256];
	WSABUF     wsaBuf;
} PER_IO_DATA, *LPPER_IO_DATA;

class ASocket : public PB::socket
{
private:
	std::thread*			_completionReadThread;
	std::thread*			_completionWriteThread;

public:
	ASocket();
	~ASocket();

public:
	bool					connect(const std::string& ip, uint16_t port);

public:
public:
	void					completionReadThreadRoutine(HANDLE completionPort);
	void					completionWriteThreadRoutine(HANDLE completionPort);
};

#endif // !__ASOCKET_H__