#ifndef __PBSOCKET_H__
#define __PBSOCKET_H__

#pragma comment(lib, "ws2_32.lib")

#include "PBObject.h"
#include "PBThread.h"
#include <Windows.h>
#include <exception>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>

namespace PB {

    class __declspec(dllexport) socket : public virtual object
    {
    private:
        static WSAData          _wsa;

    protected:
        SOCKET                  _socket;

    protected:
        socket(int af, int type, int protocol)                  throw (std::exception);
        socket(SOCKET sock);
        virtual ~socket();

    public:
        bool                    bind(short port);
        void                    close();
        bool                    peername(std::string* ip, int* port) const;

    public:
        const std::string       toString() const;

    public:
        operator                SOCKET () const;
        operator                const std::string () const;

    public:
        static void             init();
        static void             release();
    };

    class __declspec(dllexport) tcp : public socket
    {
    public:
        tcp();
        tcp(SOCKET sock);
        virtual ~tcp();

    public:
        bool                    listen();
        tcp                     accept();
        bool                    connect(const std::string& ip, short port);

        bool                    send(const std::vector<char>& data);
        bool                    recv(std::vector<char>& buffer, int size);
    };

    class __declspec(dllexport) udp : public socket
    {
    public:
        udp();
        virtual ~udp();

        bool                    sendto(const std::string& ip, short port, const std::vector<char>& bytes);
        bool                    recvfrom(std::string& ip, short* port, std::vector<char>& buffer);
    };

    class __declspec(dllexport) socket_map : private std::map<SOCKET, tcp*>
    {
    public:
        typedef std::map<SOCKET, tcp*>::iterator iterator;
        typedef std::map<SOCKET, tcp*>::const_iterator citerator;

    public:
        socket_map();
        ~socket_map();

    public:
        bool                    add(tcp* socket);
        bool                    remove(tcp*);
        void                    clear();

        iterator                begin();
        iterator                end();

        citerator               begin() const;
        citerator               end() const;

    public:
        operator                const fd_set& () const;
    };

    class __declspec(dllexport) client : public tcp
    {
    private:
        std::string             _host;
        int                     _port;
        thread                  _thread;

    protected:
        client(const std::string& host, short port);
        virtual ~client();

    public:
        bool                    connect();

    public:
        virtual void            onConnected(tcp& sock) {}
        virtual bool            onReceive(tcp& sock) { return true; }
        virtual void            onDisconnect(tcp& sock) {}

    public:
        static void             onThreadRoutine(thread* self);
    };

    class __declspec(dllexport) server : public tcp
    {
    private:
        std::string             _host;
        int                     _port;
        socket_map              _clients;
        thread                  _thread;
        bool                    _running;

    public:
        server(int port);
        virtual ~server();

    public:
        bool                    run();
        bool                    close();
        socket_map*             clients();

    public:
        virtual tcp*            onConnected(tcp& socket) { return new tcp(socket); }
        virtual void            onDisconnected(tcp& socket) { }
        virtual bool            onReceive(tcp& socket) { return false; }

    public:
        static void             onThreadRoutine(thread* t);
    };

}

#endif // !__PBSOCKET_H__
