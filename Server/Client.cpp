#include "Client.h"
#include "Room.h"

Client::Client(const socket & socket, StateChangeRoutine callback) : 
    tcp(socket), 
    Character(this->id(), callback),
    _order(-1)
{
    this->_isGenerated          = false;
    this->_isReady              = false;
}

Client::~Client()
{
}

int Client::id() const
{
    return (int)this->_socket;
}

bool Client::generated() const
{
    return this->_isGenerated;
}

void Client::generated(bool value)
{
    this->_isGenerated          = value;
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
    std::string         str = json.toStyledString();
    std::vector<char>   bytes;

    int                 size = str.length();
    char*               sizeRef = (char*)&size;
    
    bytes.insert(bytes.end(), sizeRef, sizeRef + sizeof(int));
    bytes.insert(bytes.end(), str.begin(), str.end());

    return tcp::send(bytes);
}

bool Client::recv(Json::Value & json)
{
    if(tcp::recv(this->_buffer, sizeof(int)) == false)
        return false;

    int                     size = *(int*)(this->_buffer.data());
    if(tcp::recv(this->_buffer, size) == false)
        return false;

    std::string             str(this->_buffer.begin(), this->_buffer.end());
    Json::Reader            reader;

    if(reader.parse(str, json) == false)
        return false;

    return true;
}

Json::Value& Client::toJson(Json::Value & json)
{
    __super::toJson(json);
    json["id"] = this->id();
    return json;
}
