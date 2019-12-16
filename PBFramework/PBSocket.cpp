#include "PBSocket.h"
using namespace PB;

WSAData socket::_wsa;

socket::socket(int af, int type, int protocol)
{
    this->_fd           = ::socket(af, type, protocol);
    if (this->_fd == INVALID_SOCKET)
        throw std::exception("socket error");

	// non blocking 소켓
	u_long opt = 1;
	::ioctlsocket(this->_fd, FIONBIO, &opt);
}

socket::socket(SOCKET sock)
{
    this->_fd           = sock;
}

socket::~socket()
{
}

//
// bind
//  소켓을 바인딩한다.
//
// Parameters
//  port        포트
//
// Return
//  성공시 true, 실패시 false
//
bool socket::bind(short port)
{
    struct sockaddr_in      addr    = {0,};
    addr.sin_family                 = AF_INET;
    addr.sin_port                   = htons(port);
    addr.sin_addr.s_addr            = INADDR_ANY;

    return ::bind(this->_fd, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR;
}

//
// close
//  소켓을 종료한다.
// 
// Parameters
//  없음
//
// Return
//  없음
// 
void socket::close()
{
    closesocket(this->_fd);
}

bool PB::socket::peername(std::string * ip, int * port) const
{
    struct sockaddr_in      addr = {0,};
    int                     size = sizeof(addr);
    if(::getpeername(this->_fd, (struct sockaddr *)&addr, &size) == SOCKET_ERROR)
        return false;

    if(port != NULL)
        *port = addr.sin_port;

    if(ip != NULL)
        *ip = inet_ntoa(addr.sin_addr);

    return true;
}

const std::string PB::socket::toString() const
{
    std::string             ip;
    int                     port;
    if(this->peername(&ip, &port) == false)
        return std::string("Unknown");

    return std::string(ip + ":" + std::to_string(port));
}

socket::operator SOCKET() const
{
    return this->_fd;
}

PB::socket::operator const std::string() const
{
    return this->toString();
}

//
// init
//  소켓을 사용하기 위한 초기화를 수행한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void socket::init()
{
    WSAStartup(MAKEWORD(2, 2), &_wsa);
}

//
// release
//  소켓 초기화에 사용된 메모리를 해제한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void socket::release()
{
    WSACleanup();
}

tcp::tcp() : socket(AF_INET, SOCK_STREAM, 0)
{
	this->_istream.reserve(0x1000);
	this->_ostream.reserve(0x1000);
}

tcp::tcp(SOCKET sock) : socket(sock)
{
}

tcp::~tcp()
{
}

//
// listen
//  클라이언트를 받을 준비를 한다.
//
// Parameters
//  없음
//
// Return
//  성공시 true, 실패시 false
//
bool tcp::listen()
{
    return ::listen(this->_fd, SOMAXCONN) != SOCKET_ERROR;
}

//
// accept
//  연결 요청한 클라이언트를 받는다.
//
// Parameters
//  없음
//
// Return
//  연결 요청한 클라이언트 소켓
//
tcp tcp::accept()
{
    struct sockaddr_in  addr        = {0,};
    int                 addrsize    = sizeof(addr);
    SOCKET              client      = ::accept(this->_fd, (struct sockaddr*)&addr, &addrsize);

    if (client == SOCKET_ERROR)
        throw std::exception("accept error");

    return tcp(client);
}

//
// connect
//  연결 요청을 한다.
//
// Parameters
//  ip      아이피
//  port    포트
//
// Return
//  성공시 true, 실패시 false
//
bool tcp::connect(const std::string& ip, short port)
{
    struct sockaddr_in  addr        = {0,};
    addr.sin_family                 = AF_INET;
    addr.sin_addr.s_addr            = inet_addr(ip.c_str());
    addr.sin_port                   = htons(port);

    if (addr.sin_addr.s_addr == -1)
    {
        struct hostent* entry = gethostbyname(ip.c_str());
        if (entry == NULL)
            return false;

        addr.sin_addr.s_addr = *((unsigned long *)(entry->h_addr_list[0]));
    }

    return ::connect(this->_fd, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR;
}

//
// send
//  데이터를 보낸다.
//
// Parameters
//  bytes       보낼 데이터
//
// Return
//  성공시 true, 실패시 false
//
bool tcp::send()
{
	if(this->_fd == INVALID_SOCKET)
		return false;

	if(this->_ostream.size() == 0)
		return true;

	uint32_t				sent_size = ::send(this->_fd, (const char*)this->_ostream.data(), this->_ostream.size(), 0);
	if(sent_size == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
		return false;

	if(sent_size == 0)
		return false;

	if(sent_size != SOCKET_ERROR)
		this->_ostream.erase(this->_ostream.begin(), this->_ostream.begin() + sent_size);

	return true;
}

//
// recv
//  데이터를 받는다.
//
// Parameters
//  buffer      저장될 버퍼
//  size        받을 크기
//
// Return
//  성공시 true, 실패시 false
//
bool tcp::recv()
{
	if(this->_fd == INVALID_SOCKET)
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

istream& PB::tcp::in_stream()
{
	return this->_istream;
}

ostream& PB::tcp::out_stream()
{
	return this->_ostream;
}

udp::udp() : socket(AF_INET, SOCK_DGRAM, 0)
{
}

udp::~udp()
{
}

bool udp::sendto(const std::string & ip, short port, const std::vector<char>& bytes) throw(std::exception)
{
    struct sockaddr_in  addr            = {0,};
    addr.sin_family                     = AF_INET;
    addr.sin_addr.s_addr                = inet_addr(ip.c_str());
    addr.sin_port                       = htons(port);

    int                 sendsize        = ::sendto(this->_fd, bytes.data(), bytes.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
    if(sendsize == SOCKET_ERROR)
        return false;

    return true;
}

bool udp::recvfrom(std::string & ip, short * port, std::vector<char>& stream) throw(std::exception)
{
    struct sockaddr_in  addr            = {0,};
    int                 addrsize        = sizeof(addr);

    stream.resize(4096);
    stream.clear();
    int                 recvsize        = ::recvfrom(this->_fd, stream.data(), stream.size(), 0, (struct sockaddr*)&addr, &addrsize);
    if(recvsize == SOCKET_ERROR)
        return false;

    stream.resize(recvsize);
    return true;
}

socket_map::socket_map()
{}

socket_map::~socket_map()
{
    this->clear();
}

bool socket_map::add(tcp* socket)
{
    SOCKET fd = (SOCKET)*socket;
    if(this->find(fd) != this->end())
        return false;

    const std::pair<SOCKET, tcp*> pair(fd, socket);
    this->insert(pair);
    return true;
}

bool socket_map::remove(tcp* socket)
{
    SOCKET fd = (SOCKET)*socket;
    if(this->find(fd) == this->end())
        return false;

    this->erase(fd);
    return true;
}

void socket_map::clear()
{
    for(std::map<SOCKET, tcp*>::iterator i = this->begin(); i != this->end(); i++)
        delete i->second;

    std::map<SOCKET, tcp*>::clear();
}

socket_map::iterator socket_map::begin()
{
    return __super::begin();
}

socket_map::iterator socket_map::end()
{
    return __super::end();
}

socket_map::citerator socket_map::begin() const
{
    return __super::begin();
}

socket_map::citerator socket_map::end() const
{
    return __super::end();
}

socket_map::operator const fd_set & () const
{
    fd_set                  ret = { 0, };

    for(std::map<SOCKET, tcp*>::const_iterator i = this->begin(); i != this->end(); i++)
        FD_SET((SOCKET)*i->second, &ret);

    return ret;
}

client::client(const std::string & host, short port) : _thread(client::onThreadRoutine, this)
{
    this->_host             = host;
    this->_port             = port;
}

client::~client()
{
    this->_thread.wait();
}

bool PB::client::connect()
{
    if(tcp::connect(this->_host, this->_port) == false)
        return false;

    this->onConnected(*this);
    this->_thread.run();
    return true;
}

//
// onThreadRoutine
//  쓰레드에서 동작할 함수이다.
//  recv 함수를 이용해 데이터를 받는 작업만 한다.
//  데이터를 성공적으로 받는다면 onReceive 함수를 호출한다.
//
// Parameters
//  thread      쓰레드
//
// Return
//  없음
//
void client::onThreadRoutine(thread * thread)
{
    client*                     self        = (client*)thread->parameter();
    bool                        disconnect  = false;

    while(self->onReceive(*self))
    { }

    self->onDisconnect(*self);
    self->close();
}

server::server(int port) : tcp(), _thread(this->onThreadRoutine, this)
{
    this->_running = false;
    this->bind(port);
    this->listen();
}

server::~server()
{
    this->close();
}

bool server::run()
{
    if(this->_running)
        return false;

    this->_running = true;
    this->_thread.run();
    return true;
}

bool server::close()
{
    if(this->_running == false)
        return false;

    this->_running = false;
    this->_thread.wait();
    socket::close();

    for (auto i = this->_clients.begin(); i != this->_clients.end(); i++)
    {
        this->_clients.remove(i->second);
        delete i->second;
    }
    this->_clients.clear();
    return true;
}

socket_map* server::clients()
{
    return &(this->_clients);
}

void server::onThreadRoutine(thread* t)
{
    server*                 self        = (server*)t->parameter();
    SOCKET                  fd          = (SOCKET)*self;
    std::vector<tcp*>       disconnectedList;

    while(self->_running)
    {
        fd_set                  cpyReads    = self->_clients;
        struct timeval          timeout     = { 5, 0 };

        FD_SET(fd, &cpyReads);
        int                     fdnum       = select(0, &cpyReads, 0, 0, &timeout);
        if(fdnum == SOCKET_ERROR)                               // error
            break;

        if(fdnum == 0)                                          // timeout
            continue;

        if(FD_ISSET((SOCKET)*self, &cpyReads))                  // connection request
        {
            tcp         socket      = self->accept();
            self->_clients.add(self->onConnected(socket));
            printf("[%s] Connected\n", socket.toString().c_str());
        }

        disconnectedList.clear();
        for(socket_map::iterator i = self->_clients.begin(); i != self->_clients.end(); i++)
        {
            tcp*        client      = i->second;
            SOCKET      fd          = (SOCKET)*client;
            if(FD_ISSET(fd, &cpyReads) == false)
                continue;

            if(self->onReceive(*client) == false)
            {
                printf("[%s] Disconnected\n", client->toString().c_str());
                self->onDisconnected(*client);
                disconnectedList.push_back(client);
            }
        }

        for(std::vector<tcp*>::iterator i = disconnectedList.begin(); i != disconnectedList.end(); i++)
        {
            self->_clients.remove(*i);
            delete *i;
        }
    }
}