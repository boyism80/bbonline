#include "acceptor.h"

base_session::base_session(SOCKET fd) : PB::socket(fd)
{
}

base_session::~base_session()
{
}
