#include "asocket.h"

ASocket::ASocket() : PB::socket(WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED))
{
}

ASocket::~ASocket()
{
}
