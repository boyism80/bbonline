#ifndef __ROOM_H__
#define __ROOM_H__

#include "Character.h"

class Room
{
public:
    enum State
    {
        WAIT, GAME, RESULT,
    };

private:
    int                     _id;
    std::string             _name;
    int                     _capacity;
    int                     _priest;
    State                   _state;

public:
    Room(int id, const std::string& name, int capacity, int priest, State state);
    Room(const Room& right);
    ~Room();

public:
    int                     id() const;
    const std::string       name() const;
    int                     capacity() const;
    int                     priest() const;
    State                   state() const;
};

#endif // !__ROOM_H__