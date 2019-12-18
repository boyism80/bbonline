#include "session.h"
#include "Room.h"

session::session(SOCKET fd, StateChangeRoutine callback) : 
	base_session(fd), 
    Character(this->id(), callback),
    _order(-1)
{
    this->_isReady              = false;
}

session::~session()
{
}

int session::id() const
{
    return static_cast<SOCKET>(*this);
}

bool session::ready() const
{
    return this->_isReady;
}

void session::ready(bool state)
{
    this->_isReady = state;
}

int session::order() const
{
    return this->_order;
}

void session::order(int order)
{
    this->_order = order;
}

bool session::enter(Room * room)
{
    return room->enter(this);
}

bool session::leave()
{
    Room* room = this->room();
    if(room == NULL)
        return false;

    room->leave(this);
    return true;
}

bool session::send(const Json::Value & json)
{
	Json::FastWriter	writer;
	std::string			str = writer.write(json);

	ostream&			ostream = this->out_stream();
	ostream.write_u32(str.size())
		.write(str.c_str(), str.size());

	return true;
}

Json::Value& session::toJson(Json::Value & json)
{
    __super::toJson(json);
    json["id"] = this->id();
    return json;
}
