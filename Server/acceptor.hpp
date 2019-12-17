#include "acceptor.h"

template <typename T>
base_acceptor<T>::base_acceptor(uint16_t port) : PB::socket(::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)),
_running(false),
_execute_thread(NULL)
{
	SOCKADDR_IN			address = { 0, };
	address.sin_addr.s_addr     = INADDR_ANY;
	address.sin_family			= AF_INET;
	address.sin_port			= htons(port);
	if (::bind(*this, (struct sockaddr*) & address, sizeof(address)) == SOCKET_ERROR)
		throw "cannot bind socket";

	if (::listen(*this, SOMAXCONN) == SOCKET_ERROR)
		throw "cannot listen socket";

	this->_sockets.root(*this, this);
}

template <typename T>
base_acceptor<T>::~base_acceptor()
{}

template <typename T>
bool base_acceptor<T>::do_session()
{
	struct timeval timeout;
	timeout.tv_sec  = 0;
	timeout.tv_usec = 500000;

	fd_set& reads = this->_sockets;
	fd_set	copy  = reads;

	if (::select(0, &copy, NULL, NULL, &timeout) == SOCKET_ERROR)
		return false;

	for (uint32_t i = 0; i < reads.fd_count; i++)
	{
		SOCKET fd = reads.fd_array[i];
		if (FD_ISSET(fd, &copy) == false)
			continue;

		if(fd == *this)
			this->handle_accept();
		else
			this->handle_receive((T&)*this->_sockets[fd]);
	}

	for(uint32_t i = 0; i < reads.fd_count; i++)
	{
		this->_sockets[reads.fd_array[i]]->in_stream().flush();
		this->_sockets[reads.fd_array[i]]->send();
	}
	return true;
}

template <typename T>
bool base_acceptor<T>::disconnect(SOCKET fd)
{
	this->handle_disconnected((T&)*this->_sockets[fd]);
	this->_sessions.erase(std::find(this->_sessions.begin(), this->_sessions.end(), this->_sockets[fd]));
	this->_sockets.reduce(fd);
	return true;
}

template <typename T>
bool base_acceptor<T>::execute(bool async)
{
	if (this->_running)
		return false;

	if(async)
	{
		if(this->_execute_thread != NULL)
			return false;

		this->_execute_thread = new std::thread(&base_acceptor<T>::execute, this, false);
		return true;
	}
	else
	{
		this->_running = true;
		this->_sockets.clear();
		while (this->_running)
		{
			this->do_session();
		}

		return true;
	}
}

template<class T>
inline void base_acceptor<T>::exit()
{
	this->_running = false;
	if(this->_execute_thread != NULL)
	{
		this->_execute_thread->join();
		delete this->_execute_thread;
		this->_execute_thread = NULL;
	}
}

template<class T>
inline T* base_acceptor<T>::session(uint32_t fd)
{
	auto i = this->_sockets.find(fd);
	if(i == this->_sockets.end())
		return NULL;

	return static_cast<T*>(i->second);
}

template<class T>
inline std::vector<T*>& base_acceptor<T>::sessions()
{
	return this->_sessions;
}

template <typename T>
bool base_acceptor<T>::handle_accept()
{
	SOCKADDR_IN		address			 = {0,};
	int32_t			address_size	 = sizeof(address);
	SOCKET			fd				 = ::accept(*this, (struct sockaddr*) & address, &address_size);

	this->_sockets.add(fd, (socket*)new T(fd));
	this->_sessions.push_back(static_cast<T*>(this->_sockets[fd]));

	return this->handle_connected((T&)*this->_sockets[fd]);
}

template<typename T>
inline void base_acceptor<T>::handle_receive(T& session)
{
	if(session.recv() == false || this->handle_parse(session) == false)
		this->disconnect(session);
}

template<class T>
inline T* base_acceptor<T>::operator[](uint32_t fd) const
{
	return this->session(fd);
}