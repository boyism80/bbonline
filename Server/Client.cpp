#include "Client.h"
#include "Room.h"

Client::Client(SOCKET fd, StateChangeRoutine callback) : 
	base_session(fd), 
    Character(this->id(), callback),
    _order(-1)
{
    this->_isReady              = false;
}

Client::~Client()
{
}

int Client::id() const
{
    return static_cast<SOCKET>(*this);
}

bool Client::ready() const
{
    return this->_isReady;
}

void Client::ready(bool state)
{
    this->_isReady = state;
}

int Client::order() const
{
    return this->_order;
}

void Client::order(int order)
{
    this->_order = order;
}

bool Client::enter(Room * room)
{
    return room->enter(this);
}

bool Client::leave()
{
    Room* room = this->room();
    if(room == NULL)
        return false;

    room->leave(this);
    return true;
}

bool Client::send(const Json::Value & json)
{
	Json::FastWriter	writer;
	std::string			str = writer.write(json);

	ostream&			ostream = this->out_stream();
	ostream.write_u32(str.size())
		.write(str.c_str(), str.size());

	return true;
}

Json::Value& Client::toJson(Json::Value & json)
{
    __super::toJson(json);
    json["id"] = this->id();
    return json;
}
