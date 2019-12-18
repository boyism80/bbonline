#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "acceptor.h"
#include "Character.h"
using namespace PB;

class Room;

class session : public base_session, public Character
{
//private:
    bool                    _connected;
    bool                    _isReady;
    int                     _order;             //게임방의 슬롯 순서

public:
    session(SOCKET fd, StateChangeRoutine callback = NULL);
    ~session();

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