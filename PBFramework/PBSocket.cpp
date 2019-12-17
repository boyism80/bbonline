#include "PBSocket.h"
using namespace PB;

WSAData socket::_wsa;

PB::socket::socket(SOCKET socket) : _fd(INVALID_SOCKET)
{
	this->_fd = socket;

	u_long opt = 1;
	::ioctlsocket(this->_fd, FIONBIO, &opt);

	this->_istream.reserve(0x1000);
	this->_ostream.reserve(0x1000);
}

PB::socket::~socket()
{
}

bool PB::socket::valid() const
{
	return this->_fd != INVALID_SOCKET;
}

bool PB::socket::send()
{
	if(this->_ostream.size() == 0)
		return true;

	if (this->valid() == false)
		return false;

	uint32_t				sent_size = ::send(this->_fd, (const char*)this->_ostream.data(), this->_ostream.size(), 0);
	if(sent_size == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
		return false;

	if(sent_size == 0)
		return false;

	if(sent_size != SOCKET_ERROR)
		this->_ostream.erase(this->_ostream.begin(), this->_ostream.begin() + sent_size);

	return true;
}

bool PB::socket::recv()
{
	if (this->valid() == false)
		return false;

	uint32_t				space		= this->_istream.capacity() - this->_istream.size();
	if(space == 0)
		return false;

	char*					buffer		= new char[space];
	bool					success		= true;

	try
	{
		uint32_t			recv_size	= ::recv(this->_fd, buffer, space, 0);
		if(recv_size == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
			throw std::exception();

		if(recv_size == 0)
			throw std::exception();

		this->_istream.insert(this->_istream.end(), buffer, buffer + recv_size);

		delete[] buffer;
		return true;
	}
	catch(std::exception&)
	{
		delete[] buffer;
		return false;
	}

	delete[] buffer;
	return success;
}

void PB::socket::close()
{
	::closesocket(this->_fd);
}

PB::istream& PB::socket::in_stream()
{
	return this->_istream;
}

PB::ostream& PB::socket::out_stream()
{
	return this->_ostream;
}

PB::socket::operator SOCKET() const
{
	return this->_fd;
}

void PB::socket::init()
{
	WSAStartup(MAKEWORD(2, 2), &_wsa);
}

void PB::socket::release()
{
	WSACleanup();
}

PB::socket_map::socket_map() : _root(NULL)
{
	FD_ZERO(&this->_fd_set);
}

PB::socket_map::~socket_map()
{
	this->clear();
}

bool PB::socket_map::add(SOCKET fd, PB::socket* socket)
{
	if(socket == NULL)
		return false;

	if (FD_ISSET(fd, &this->_fd_set))
		return false;

	FD_SET(fd, &this->_fd_set);
	this->insert(std::pair<SOCKET, PB::socket*>(fd, socket));
	return true;
}

bool PB::socket_map::root(SOCKET fd, socket* socket)
{
	if(this->add(fd, socket) == false)
		return false;

	this->_root = socket;
	return true;
}

bool PB::socket_map::reduce(SOCKET fd)
{
	if (FD_ISSET(fd, &this->_fd_set) == false)
		return false;

	socket* base_session = this->get(fd);

	FD_CLR(fd, &this->_fd_set);
	this->erase(fd);
	delete base_session;
	return true;
}

void PB::socket_map::clear()
{
	for (auto i = this->begin(); i != this->end(); i++)
	{
		if(i->second == this->_root)
			continue;

		delete i->second;
	}

	FD_ZERO(&this->_fd_set);
	__super::clear();

	this->add(*this->_root, this->_root);
}

PB::socket* PB::socket_map::get(SOCKET fd) const
{
	return __super::find(fd)->second;
}

bool PB::socket_map::contains(SOCKET fd) const
{
	return FD_ISSET(fd, &this->_fd_set);
}

PB::socket* PB::socket_map::operator[](SOCKET fd)
{
	return std::map<SOCKET, socket*>::operator[](fd);
}

PB::socket_map::operator fd_set& ()
{
	return this->_fd_set;
}