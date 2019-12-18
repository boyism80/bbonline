#ifndef __PBSOCKET_H__
#define __PBSOCKET_H__

#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <exception>
#include <vector>
#include <map>
#include <string>
#include "PBStream.h"

namespace PB {

class __declspec(dllexport) socket : public virtual object
{
private:
	static WSAData          _wsa;

private:
	SOCKET					_fd;
	istream					_istream;
	ostream					_ostream;

protected:
	socket(SOCKET socket);
public:
	virtual ~socket();

protected:
	bool					valid() const;

public:
	bool					send();
	bool					recv();
	void					close();

public:
	istream&				in_stream();
	ostream&				out_stream();

public:
	operator				SOCKET () const;

public:
	static void				init();
	static void				release();
};


class __declspec(dllexport) socket_map : private std::map<SOCKET, socket*>
{
private:
	fd_set					_fd_set;
	socket*					_root;

public:
	using std::map<SOCKET, socket*>::find;
	using std::map<SOCKET, socket*>::begin;
	using std::map<SOCKET, socket*>::end;

public:
	socket_map();
	~socket_map();

public:
	bool					add(SOCKET fd, socket* socket);
	bool					root(SOCKET fd, socket* socket);
	bool					reduce(SOCKET fd);
	void					clear();
	socket*					get(SOCKET fd) const;
	bool					contains(SOCKET fd) const;

public:
	socket*					operator [] (SOCKET fd);
	operator				fd_set& ();
};

}

#endif // !__PBSOCKET_H__
