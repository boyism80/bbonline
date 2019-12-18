#ifndef __ACCEPTOR_H__
#define	__ACCEPTOR_H__

#include "PBSocket.h"
#include <thread>

using namespace PB;

class base_session : public socket
{
public:
	base_session(SOCKET fd);
	virtual ~base_session();
};

template <class T>
class base_acceptor : protected PB::socket
{
public:
	typedef std::vector<T*> session_list;

private:
	bool					_running;
	PB::socket_map			_sockets;
	session_list			_sessions;
	std::thread*			_execute_thread;


protected:
	base_acceptor(uint16_t port);
	virtual ~base_acceptor();

private:
	bool					do_session();
	bool					disconnect(SOCKET fd);

public:
	bool					execute(bool async = false);
	void					exit();
	T*						session(uint32_t fd);
	std::vector<T*>&		sessions();

public:
	bool					handle_accept();
	void					handle_receive(T& base_session);

public:
	virtual bool			handle_connected(T& base_session) { return true; }
	virtual bool			handle_disconnected(T& base_session) { return true; }
	virtual bool			handle_parse(T& base_session) = 0;

public:
	T*						operator [] (uint32_t fd) const;
};

#include "acceptor.hpp"

#endif // !__ACCEPTOR_H__