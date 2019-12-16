#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "PBSocket.h"
#include "Character.h"
using namespace PB;

class Room;

class Client : public tcp, public Character
{
private:
    std::vector<char>       _buffer;

private:
    bool                    _connected;
    bool                    _isGenerated;
    bool                    _isReady;
    int                     _order;             //게임방의 슬롯 순서

public:
    Client(const socket& socket, StateChangeRoutine callback);
    ~Client();

public:
    int                     id() const;
    bool                    generated() const;
    void                    generated(bool value);

    bool                    ready() const;
    void                    ready(bool state);

    int                     order() const;
    void                    order(int order);

    bool                    enter(Room* room);
    bool                    leave();

public:
    bool                    send(const Json::Value& json);
    //bool                    recv(Json::Value& json);

public:
    virtual Json::Value&    toJson(Json::Value& json);
};

#endif // !__CLIENT_H__