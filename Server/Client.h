#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "PBThread.h"
#include "PBSocket.h"
#include "Character.h"
#include "acceptor.h"
using namespace PB;

class Room;

class Client : public base_session, public Character
{
private:
    std::vector<char>       _buffer;

private:
    bool                    _connected;
    bool                    _isReady;
    int                     _order;             //게임방의 슬롯 순서

public:
    Client(SOCKET fd, StateChangeRoutine callback = NULL);
    ~Client();

public:
    int                     id() const;

    bool                    ready() const;
    void                    ready(bool state);

    int                     order() const;
    void                    order(int order);

    bool                    enter(Room* room);
    bool                    leave();

public:
    bool                    send(const Json::Value& json);

public:
    virtual Json::Value&    toJson(Json::Value& json);
};

#endif // !__CLIENT_H__