#include "Room.h"

Room::Room(int id, const std::string & name, int capacity, int priest, State state)
{
    this->_id           = id;
    this->_name         = name;
    this->_capacity     = capacity;
    this->_priest       = priest;
    this->_state        = state;
}

Room::Room(const Room & right)
{
    this->_id           = right._id;
    this->_name         = right._name;
    this->_capacity     = right._capacity;
    this->_priest       = right._priest;
    this->_state        = right._state;
}

Room::~Room()
{
}

int Room::id() const
{
    return this->_id;
}

const std::string Room::name() const
{
    return this->_name;
}

int Room::capacity() const
{
    return this->_capacity;
}

int Room::priest() const
{
    return this->_priest;
}

Room::State Room::state() const
{
    return this->_state;
}
