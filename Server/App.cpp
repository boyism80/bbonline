#include "App.h"
#include <stdio.h>

App* App::_instance     = NULL;

App::App(short port) : server(port)
{
    this->bind(port);
    this->listen();

    this->loadMaps("Resources/maps");

    this->addEvent("connect",       &App::connectRoutine);
    this->addEvent("disconnect",    &App::disconnectRoutine);
    this->addEvent("create room",   &App::createRoomRoutine);
    this->addEvent("enter room",    &App::enterRoomRoutine);
    this->addEvent("leave room",    &App::disconnectRoutine);
    this->addEvent("room list",     &App::roomListRoutine);
    this->addEvent("stand by",      &App::standByRoutine);
    this->addEvent("ready",         &App::readyRoutine);
    this->addEvent("move",          &App::moveRoutine);
    this->addEvent("stop",          &App::stopRoutine);
    this->addEvent("map",           &App::mapRoutine);
    this->addEvent("generate",      &App::generateRoutine);
    this->addEvent("jump",          &App::jumpRoutine);
    this->addEvent("shot bubble",   &App::shootBubbleRoutine);
}

App::~App()
{
    for(std::unordered_map<int, Room*>::iterator i = this->_rooms.begin(); i != this->_rooms.end(); i++)
        delete i->second;

    for (auto i = this->_maps.begin(); i != this->_maps.end(); i++)
        delete i->second;

    this->close();
}

//
// loadMaps
//  �������� ���� ��´�.
//
// Parameters
//  �������� �����ϴ� ���丮 ���
//
// Return
//  ������ true, ���н� false�� ����
//
bool App::loadMaps(const std::string & path)
{
    std::string             wildcard(path);
    wildcard.append("\\*.pbm");

    WIN32_FIND_DATAA        data    = {0,};
    HANDLE                  handle  = ::FindFirstFileA(wildcard.c_str(), &data);
    if(handle == INVALID_HANDLE_VALUE)
        return false;

    do
    {
        if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // ���丮 ������ ��� ����
        }
        else
        {
            Map*            map     = new Map(path + "/" + data.cFileName);
            this->_maps.insert(std::make_pair(data.cFileName, map));
        }
    } while(::FindNextFileA(handle, &data) != 0);

    ::FindClose(handle);
    return true;
}

bool App::addEvent(const std::string & method, BBPacketRoutine callbackRoutine)
{
    this->_eventTable.insert(std::make_pair(method, callbackRoutine));
    return true;
}

//
// methodEventProc
//  ���޹��� json�� method �ʵ带 Ȯ���Ͽ� �����Ǵ� json���� �����Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  json        ���޹��� json
//
// Return
//  ����
//
void App::methodEventProc(Client* client, Json::Value& json, uint8_t* binary, uint32_t binary_size)
{
    std::string             method  = json["method"].asString();        // method �ʵ�

    try
    {
        // �̺�Ʈ ���̺��� �ش� method�� �����Ǵ� �̺�Ʈ�� �ִ��� �˻��Ѵ�.
        std::unordered_map<std::string, BBPacketRoutine>::iterator i = this->_eventTable.find(method);
        if(i == this->_eventTable.end())
            throw std::exception("Undefined 'method' field");


        // ������ json ��ü
        Json::Value         response;
        response["method"]              = method;
        response["success"]             = true;


        // ���� Ŭ���̾�Ʈ�� �� ��ȣ�� ���� ���Ѵ�.
        Room*               room        = client->room();


        // method�� �����Ǵ� ��ƾ�� ����
        SendScope           scope       = SendScope::SELF;
        if((this->*i->second)(*client, json, response, scope) == false)
            return;

        // ������ ����� ������ �°� �������ش�.
csection::enter("room");
        //switch(scope)
        //{
        //case SendScope::ALL:
        //    this->sendAll(response);
        //    break;

        //case SendScope::ROOM:
        //    this->sendRoom(client->room() != NULL ? client->room() : room, response);
        //    break;

        //case SendScope::ROBBY:
        //    this->sendRobby(response);
        //    break;

        //case SendScope::SELF:
        //    client->send(response);
        //    break;
        //}

csection::leave("room");
    }
    catch(std::exception& e)
    {
        Json::Value         json;
        json["method"]      = method;
        json["error"]       = e.what();
        json["success"]     = false;

        //client->send(json);
csection::leave("room");
    }
}

//
// destroyRoom
//  ���ӹ��� �����Ѵ�.
//
// Parameters
//  ������ ���� ��
//
// Return
//  ����
//
void App::destroyRoom(Room * room)
{
    this->_rooms.erase(room->id());
    room->destroy();
    delete room;
}

//
// sendRoom
//  �ش� ���ӹ濡 �����ϴ� Ŭ���̾�Ʈ�鿡�Ը� ��Ŷ�� ������.
//
// Parameters
//  room            ���ӹ�
//  json            ���� ������
//
// Return
//  ������ true, ���н� false�� ����
//
bool App::sendRoom(Room * room, Json::Value& json)
{
    if(room == NULL)
        return false;

csection::enter("room");
    for(int i = 0; i < room->capacity(); i++)
    {
        Client*             client = room->client(i);
        if(client == NULL)
            continue;

        client->send(json);
    }
csection::leave("room");
    return true;
}

//
// sendRobby
//  �κ� �����ϴ� Ŭ���̾�Ʈ�鿡�� ��Ŷ�� ������.
//
// Parameters
//  json        ���� ������
//
// Return
//  ������ true, ���н� false�� ����
//
bool App::sendRobby(Json::Value & json)
{
    socket_map*         clients     = this->clients();
    for(socket_map::iterator i = clients->begin(); i != clients->end(); i++)
    {
        Client*             client      = (Client*)i->second;
        if(client->entered())
            continue;

        client->send(json);
    }

    return true;
}

//
// sendAll
//  ��� Ŭ���̾�Ʈ�鿡�� �����͸� ������.
//
// Parameters
//  json        ���� ������
//
// Return
//  ������ true, ���н� false�� ����
//
bool App::sendAll(Json::Value & json)
{
    socket_map*         clients     = this->clients();
    for(socket_map::iterator i = clients->begin(); i != clients->end(); i++)
    {
        Client*             client      = (Client*)i->second;
        client->send(json);
    }

    return true;
}

//
// collision
//  �ʰ� ������Ʈ�� �浹�� ó���Ѵ�.
//
// Parameters
//  mapName         �浹ó���� �� �̸�
//  life            �浹ó���� ������Ʈ
//  elapsedTime     ���� �ð�
//
// Return
//  ������ true, ���н� false�� ����
//
bool App::collision(const std::string& mapName, Life& life, float elapsedTime, bool useFlag, PBCollisionInitRoutine initRoutine, PBCollisionInitRoutine releaseRoutine, PBCollisionRoutine collisionRoutine)
{
    // ���� �̸��� �����Ǵ� ���� ��´�.
    Map*                    map     = this->_maps[mapName];
    if(map == NULL)
        return false;

    Json::Value             parameters;

    // ������Ʈ�� y������ ���� �̵��� �Ѵ�.
    //float                 yinc    = -life.velocity().y * elapsedTime;
    //life.move(0, yinc);

    // �̵��� ������ �浹������ ���Ѵ�.
    if(initRoutine != NULL)
        initRoutine(map, life, elapsedTime, parameters);
    

    // ���� ���°� �ƴ� ��쿡�� y�� �浹üũ �˻縦 �Ѵ�.
    int maxRow = min(map->row(), max(0, (int)(life.collisionRect().bottom / map->tileHeight()) + 1));
    int maxColumn = min(map->col(), max(0, (int)(life.collisionRect().right / map->tileWidth()) + 1));
    for (int row = max(0, (int)(life.collisionRect().top / map->tileHeight())); row < maxRow; row++)
    {
        for (int col = max(0, (int)(life.collisionRect().left / map->tileWidth())); col < maxColumn; col++)
        {
            // �� Ÿ���� ��´�.
            const Map::Tile*    tile = map->get(row, col);
            if (tile == NULL)
                continue;

            // �� Ÿ���� �浹 ������ ���Ѵ�.
            rect_f              collisionTileRect = map->collisionRect(row, col);

            // �� Ÿ���� �浹 �÷��׸� ���Ѵ�.
            char                collisionTileFlag = tile->flag();

            // �浹���� �ʾҴٸ� ����
            if (collisionTileRect.contains(life.collisionRect()) == false)
                continue;

            bool enabled = false;
            bool contains = false;
            bool comparePosition = false;
            bool extensions = false;

            enabled = (useFlag == false || (collisionTileFlag & Map::Tile::CollisionFlag::Top));
            contains = life.containsTile(collisionTileRect, "outer", false, true, false, false);
            comparePosition = life.comparePosition(collisionTileRect, "lesser", false, false, false, true);
            extensions = (life.collisionRect().bottom - life.collisionRect().height() * 0.2f < collisionTileRect.top);
            if (enabled && contains && comparePosition && extensions)
            {
                if (collisionRoutine != NULL)
                    collisionRoutine(map, row, col, collisionTileRect, life, elapsedTime, parameters, CollisionType::TOP);
            }

            enabled = (useFlag == false || (collisionTileFlag & Map::Tile::CollisionFlag::Bottom));
            contains = life.containsTile(collisionTileRect, "inner", true, false, true, false) && life.containsTile(collisionTileRect, "outer", false, false, false, true);
            if (life.isJumping() == false)
                contains = contains && life.comparePosition(collisionTileRect, "greater", false, false, false, true);
            comparePosition = true;
            extensions = true;

            if (enabled && contains && comparePosition && extensions)
            {
                if (collisionRoutine != NULL)
                    collisionRoutine(map, row, col, collisionTileRect, life, elapsedTime, parameters, CollisionType::BOTTOM);
            }
            

            enabled = (useFlag == false || (collisionTileFlag & Map::Tile::CollisionFlag::Left));
            contains = life.containsTile(collisionTileRect, "inner", false, true, false, true) && life.containsTile(collisionTileRect, "outer", true, false, false, false);
            comparePosition = life.comparePosition(collisionTileRect, "lesser", true, false, false, false);
            extensions = life.collisionRect().bottom - life.collisionRect().height() * 0.25f > collisionTileRect.top;
            if (enabled && contains && comparePosition && extensions)
            {
                if (collisionRoutine != NULL)
                    collisionRoutine(map, row, col, collisionTileRect, life, elapsedTime, parameters, CollisionType::LEFT);
            }

            enabled = (useFlag == false || (collisionTileFlag & Map::Tile::CollisionFlag::Right));
            contains = life.containsTile(collisionTileRect, "inner", false, true, false, true) && life.containsTile(collisionTileRect, "outer", false, false, true, false);
            comparePosition = life.comparePosition(collisionTileRect, "greater", false, false, true, false);
            extensions = life.collisionRect().bottom - life.collisionRect().height() * 0.25f > collisionTileRect.top;
            if (enabled && contains && comparePosition && extensions)
            {
                if (collisionRoutine != NULL)
                    collisionRoutine(map, row, col, collisionTileRect, life, elapsedTime, parameters, CollisionType::RIGHT);
            }
        }
    }

    if(releaseRoutine != NULL)
        releaseRoutine(map, life, elapsedTime, parameters);
}

//
// instance
//  ���Ӽ����� �ν��Ͻ��� ��´�.
//
// Parameters
//  ����
//
// Return
//  ���Ӽ����� �ν��Ͻ��� ����
//
App* App::instance()
{
    if(App::_instance == NULL)
        App::_instance      = new App(PORT);

    return App::_instance;
}

//
// release
//  ���Ӽ����� �ν��Ͻ� �޸𸮸� �����Ѵ�.
//
// Parameters
//  ����
//
// Return
//  ����
//
void App::release()
{
    if(App::_instance != NULL)
        delete App::_instance;
}

//
// connectRoutine
//  �����û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::connectRoutine(Client& client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    response["id"]                  = client.id();
    return true;
}

//
// disconnectRoutine
//  ����������û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::disconnectRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if(client.entered() == false)
        throw std::exception("���濡 �����ϴ�.");
    
csection::enter("room");
    Room*               room = client.room();

    room->leave(&client);

    if(room->isEmpty())
    {
        this->_rooms.erase(room->id());

        Json::Value jsonRooms(Json::arrayValue);
        for (auto i = this->_rooms.begin(); i != this->_rooms.end(); i++)
        {
            Json::Value     jsonRoom;
            jsonRoom["id"] = i->second->id();
            jsonRoom["name"] = i->second->name();
            jsonRoom["capacity"] = i->second->capacity();
            jsonRoom["state"] = (int)i->second->state();
            jsonRoom["client count"] = i->second->clientCount();
            jsonRooms.append(jsonRoom);
        }

        response["id"] = client.id();
        response["rooms"] = jsonRooms;
        response["deleted room"] = room->id();
        scope = SendScope::ROBBY;
    }
    else
    {
        Json::Value     users(Json::arrayValue);

        for(int i = 0; i < room->capacity(); i++)
        {
            auto client = room->client(i);
            if(client == NULL)
                continue;

            Json::Value user;
            user["id"] = client->id();
            user["order"] = client->order();
            user["ready"] = client->ready();
            user["priest"] = client->id() == room->priest()->id();
            users.append(user);
        }

        response["id"]                  = client.id();
        response["users"]               = users;
        scope                           = SendScope::ROOM;
    }
csection::leave("room");

    Json::Value exit(response);
    exit["mine"] = true;
    client.send(exit);

    return true;
}

//
// createRoomRoutine
//  ���ӹ� ���� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::createRoomRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    std::string         title       = request["name"].asString();
    int                 capacity    = request["capacity"].asInt();
    if(capacity < 0 || capacity > MAX_CLIENT_COUNT_IN_ROOM)
        throw std::exception("1~8�� ���� �����ϵ��� �����ؾ� �մϴ�.");

    if(client.entered())
        throw std::exception("�̹� �濡 ������ ���·δ� ������ �� �����ϴ�.");

    Room*               room        = new Room(title, &client, capacity);

csection::enter("room");
    this->_rooms.insert(std::make_pair(room->id(), room));

    if(client.enter(room) == false)
        throw std::exception("������ �濡 ������ �� �����ϴ�.");

    Json::Value jsonRooms(Json::arrayValue);
    for(auto i = this->_rooms.begin(); i != this->_rooms.end(); i++)
    {
        Json::Value     jsonRoom;
        jsonRoom["id"] = i->second->id();
        jsonRoom["name"] = i->second->name();
        jsonRoom["capacity"] = i->second->capacity();
        jsonRoom["state"] = (int)i->second->state();
        jsonRoom["client count"] = i->second->clientCount();
        jsonRooms.append(jsonRoom);

        if(room->id() == i->second->id())
            response["created room"] = jsonRoom;
    }

    response["mine"]        = false;
    response["rooms"]       = jsonRooms;
    scope                   = SendScope::ROBBY;

    Json::Value     json;
    json["method"] = request["method"].asString();
    json["mine"] = true;
    json["success"] = true;
    client.send(json);
csection::leave("room");

    return true;
}

//
// enterRoomRoutine
//  ���ӹ� ���� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::enterRoomRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if(client.entered())
        throw std::exception("�̹� ���濡 �ֽ��ϴ�.");

    int                 roomIndex   = request["id"].asInt();

csection::enter("room");
    std::unordered_map<int, Room*>::iterator i = this->_rooms.find(roomIndex);
    if(i == this->_rooms.end())
    {
csection::leave("room");
        throw std::exception("������ ã�� �� �����ϴ�.");
    }

    Room*               room        = this->_rooms[roomIndex];
    if(client.enter(room) == false)
    {
        throw std::exception("�濡 ������ �� �����ϴ�.");
csection::leave("room");
    }
    //client.enterRoom(roomIndex);

    Character&          character   = client;
    scope                           = SendScope::ROOM;
csection::leave("room");
    return true;
}

//
// roomListRoutine
//  ���ӹ� ����Ʈ ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::roomListRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    Json::Value jsonRooms(Json::arrayValue);

csection::enter("room");
    
    for (auto i = this->_rooms.begin(); i != this->_rooms.end(); i++)
    {
        Json::Value     jsonRoom;
        jsonRoom["id"] = i->second->id();
        jsonRoom["name"] = i->second->name();
        jsonRoom["capacity"] = i->second->capacity();
        jsonRoom["state"] = (int)i->second->state();
        jsonRoom["client count"] = i->second->clientCount();
        jsonRooms.append(jsonRoom);
    }
csection::leave("room");

    response["rooms"]           = jsonRooms;
    return true;
}

bool App::standByRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    Json::Value         userList(Json::arrayValue);
    //int                   roomIndex = client.currentRoom();
    Room*               room = client.room();
    if (room == NULL)
        throw std::exception("�ùٸ��� ���� ���� �ε����Դϴ�.");

    //Room*                 room = this->_rooms[roomIndex];

    auto                clients = room->clients();
    for(int i = 0; i < room->capacity(); i++)
    {
        Client*         existed = room->client(i);
        if(existed == NULL)
            continue;

        Json::Value     user;

        user["id"]      = existed->id();
        user["order"]   = existed->order();
        user["priest"]  = existed->id() == room->priest()->id();
        user["ready"]   = existed->ready();
        userList.append(user);
    }

    response["id"]      = room->id();
    response["name"]    = room->name();
    response["capacity"] = room->capacity();
    response["users"]   = userList;
    scope               = SendScope::ROOM;

    return true;
}

bool App::readyRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    Json::Value         userList(Json::arrayValue);
    //int                   roomIndex = client.currentRoom();
    Room*               room = client.room();;

    if (room == NULL)
        throw std::exception("�ùٸ��� ���� ���� �ε����Դϴ�.");

    //auto              room = this->_rooms[roomIndex];
    if (room->state() != Room::State::WAIT)
        throw std::exception("������� ���� �ƴմϴ�.");

    auto                priest = room->priest();
    bool                isPriest = (client.id() == priest->id());

    auto                clients = room->clients();
    if (isPriest)
    {
        for(int i = 0; i < room->capacity(); i++)
        {
            Client*     existed = room->client(i);
            if(existed == NULL)
                continue;

            if (existed->id() == client.id())
                continue;

            if (existed->ready() == false)
                throw std::exception("��� ������ �غ� ���¿��� �մϴ�.");
        }

        for (int i = 0; i < room->capacity(); i++)
        {
            if(room->client(i) == NULL)
                continue;

            room->client(i)->ready(false);
        }

        thread::run(gameThreadRoutine, room);

        response["state"] = "in game";
        room->state(Room::State::GAME);
    }
    else
    {
        client.ready(!client.ready());

        for (int i = 0; i < room->capacity(); i++)
        {
            Client*     existed = room->client(i);
            if(existed == NULL)
                continue;

            Json::Value user;
            user["id"] = existed->id();
            user["order"] = existed->order();
            user["ready"] = existed->ready();
            user["priest"] = existed->id() == room->priest()->id();
            userList.append(user);
        }
        response["users"] = userList;
        response["state"] = "idle";
    }

    scope = SendScope::ROOM;
    return true;
}

//
// moveRoutine
//  ĳ���� �̵� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::moveRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if(client.entered() == false)
        throw std::exception("���濡 �����ϴ�.");

    Character::Direction        direction   = request["direction"].asString().compare("left") == 0 ? Character::Direction::Left : Character::Direction::Right;
    Character&      character   = client;
    if(character.isAlive() == false)
        return false;

    character.moveX(direction);
    //response["id"]                = client.id();
    //response["direction"]     = request["direction"];
    //scope                     = SendScope::ROOM;

    return false;
}

//
// stopRoutine
//  ĳ���� ���� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::stopRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if(client.entered() == false)
        throw std::exception("���濡 �����ϴ�.");

    Character::Direction        direction   = request["direction"].asString().compare("left") ? Character::Direction::Left : Character::Direction::Right;
    Character&      character   = client;
    character.stop();

    response["id"]              = client.id();
    scope                       = SendScope::ROOM;

    return true;
}

//
// mapRoutine
//  �� ���� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::mapRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if(client.entered() == false)
        throw std::exception("���濡 �����ϴ�.");

csection::enter("room");
    //Room*                     room        = this->_rooms[client.currentRoom()];
    Room*                       room        = client.room();
    std::string                 mapName     = room->mapName();
    auto                        i           = this->_maps.find(mapName);
    if(i == this->_maps.end())
    {
csection::leave("room");
        throw std::exception("Cannot find map file");
    }


    Map*                        currentMap  = this->_maps[mapName];
    response["row"]                         = currentMap->row();
    response["col"]                         = currentMap->col();
    response["tile width"]                  = currentMap->tileWidth();
    response["tile height"]                 = currentMap->tileHeight();
    response["data"]                        = Json::Value(Json::arrayValue);

    for(int col = 0; col < currentMap->col(); col++)
    {
        Json::Value             colmap(Json::arrayValue);

        for(int row = 0; row < currentMap->row(); row++)
        {
            const Map::Tile*    mapTileName = currentMap->get(row, col);
            if(mapTileName == NULL)
                colmap.append(Json::nullValue);
            else
                colmap.append(mapTileName->id());
        }
        response["data"].append(colmap);
    }
csection::leave("room");
    
    return true;
}

//
// generateRoutine
//  ���������� ���� �ʱ����� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::generateRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if(client.entered() == false)
        throw std::exception("���濡 �����ϴ�.");

    response["user"]                = Json::Value(Json::arrayValue);

csection::enter("room");
    Room*               room        = client.room();
    for (int i = 0; i < room->capacity(); i++)
    {
        Client*         existed     = room->client(i);
        if(existed == NULL)
            continue;

        Character&      character = *existed;

        Json::Value     user;
        user["id"]                  = character.id();
        user["x"]                   = character.xPos();
        user["y"]                   = character.yPos();
        user["width"]               = character.collisionRect().width();
        user["height"]              = character.collisionRect().height();
        response["user"].append(user);
    }

    response["map"]                 = Json::Value();
    std::string         mapName     = room->mapName();
    if (this->_maps.find(mapName) == this->_maps.end())
    {
csection::leave("room");
        throw std::exception("Cannot find map file");
    }

    Map*                map         = this->_maps[mapName];
    response["map"]["bgm"]          = map->bgm();
    response["map"]["row"]          = map->row();
    response["map"]["col"]          = map->col();
    response["map"]["tile width"]   = map->tileWidth();
    response["map"]["tile height"]  = map->tileHeight();
    response["map"]["data"]         = Json::Value(Json::arrayValue);

    for (int row = 0; row < map->row(); row++)
    {
        Json::Value     rowmap(Json::arrayValue);

        for (int col = 0; col < map->col(); col++)
        {
            const Map::Tile*    mapTileName = map->get(row, col);
            if(mapTileName == NULL)
                rowmap.append(Json::nullValue);
            else
                rowmap.append(mapTileName->id());
        }
        response["map"]["data"].append(rowmap);
    }

    response["level"]               = room->level();
csection::leave("room");
    return true;
}

//
// jumpRoutine
//  ���� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::jumpRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if (client.entered() == false)
        throw std::exception("���濡 �����ϴ�.");
    
    Character&              character   = client;
    if(character.isAlive() == false)
        return false;

    bool                    result      = character.jump();

    response["id"]                      = client.id();
    response["success"]                 = result;
    scope                               = SendScope::ROOM;
    return false;
}

//
// shootBubbleRoutine
//  ���� �߻� ��û�� ���� ������ ó���Ѵ�.
//
// Parameters
//  client      ��û�� Ŭ���̾�Ʈ
//  request     ��û�� ��Ŷ
//  response    ������ ��Ŷ
//  scope       ������ ����
//
// Return
//  �����Ϸ��� true, �������� �������� false
//
bool App::shootBubbleRoutine(Client & client, const Json::Value & request, Json::Value & response, SendScope& scope)
{
    if (client.entered() == false)
        throw std::exception("���濡 �����ϴ�.");

    Character&      character       = client;
csection::enter("room");
    Room*           room            = client.room();
    Bubble*         bubble          = character.shotBubble();
csection::leave("room");

    if(bubble == NULL)
        return false;
    
    room->enter(bubble);
    response["id"]                  = client.id();
    scope                           = SendScope::ROOM;
    return true;
}

//
// gameThreadRoutine
//  ������ ����Ǵ� ���� ������Ʈ�� �������� ó���Ѵ�.
//
// Parameters
//  thread          ������ ��ü
//
// Return
//  ����
//
void App::gameThreadRoutine(thread * thread)
{
    Room*                   room                = (Room*)thread->parameter();   // ���ӹ�(�Ķ���ͷ� �Ѿ��)
    int                     fps                 = 60;                           // 1�ʿ� 30�� ������Ʈ�Ѵ�.
    int                     begin               = ::GetTickCount();             // ������ ó���ϱ� ������ �ð��� ����
    float                   duration            = 1000 / fps;                   // �ѹ� ó���ϴµ� �ɷ��� �ϴ� �ð�
    float                   elapsedTime         = 0.0f;                         // ���� ���� �ð�
    float                   playTime            = 0.0f;

csection::enter("room");
    room->init();
csection::leave("room");

    App*                    app = App::instance();

    while (true)
    {
csection::enter("room");
        if(room->isEmpty())         // ���ӹ濡 ������ Ŭ���̾�Ʈ�� ���ٸ� ������ ����
        {
#if defined DEBUG | defined _DEBUG
            printf("%d�� ���� ���� ������� ��� ����ڰ� �����Ͽ����Ƿ� �ı��˴ϴ�.\n", room->id());
#endif
csection::leave("room");
            break;
        }

        if(room->isLose())
        {
            Json::Value     response;
            response["method"]              = "lose game";
            app->sendRoom(room, response);
csection::leave("room");
            break;
        }


        if(room->isClear())                     // ���ӹ濡 ������ �� �̻� �������� �ʴ´ٸ� ���� ���������� �̵�
        {
            Json::Value     response;

            if(room->nextLevel())               // ���̻� �̵��� ���������� ���ٸ� ����Ŭ���� ó��
            {
                response["method"]          = "clear game";
                app->sendRoom(room, response);
csection::leave("room");
                break;                          // ���� Ŭ���� �� ������ ����
            }
            else
            {
                // ĳ������ ��ġ�� ��ȭ��Ų��.
                Map*                map     = app->_maps[room->mapName()];
                for (int i = 0; i < room->capacity(); i++)
                    room->respawn(i, map->respawnPoint(i));

                // �� �κ��� ���߿� �� ������ ó���ؾ��� �� ����. �ӽ÷� ������ �߰����ش�.
                for (auto i = map->enemies().begin(); i != map->enemies().end(); i++)
                    room->enter(new Enemy(**i, enemyStateChangeRoutine));


                // ���������� Ŭ�����ߴٰ� �˷��ش�.
                response["method"]          = "clear stage";
                response["level"]           = room->level();
                app->sendRoom(room, response);
            }
        }

        // Character ������Ʈ
        for(int i = 0; i < room->capacity(); i++)
        {
            Client*         existed = room->client(i);
            if(existed == NULL)
                continue;

            Character&      character = *existed;
            character.update(elapsedTime);
            app->collision(room->mapName(), character, elapsedTime, true, collisionLifeInitRoutine, collisionLifeReleaseRoutine, collisionCharacterRoutine);
        }

        // Enemy ������Ʈ
        for (auto i = room->enemies().begin(); i != room->enemies().end(); i++)
        {
            Enemy&          enemy = *(*i);

            enemy.update(elapsedTime);
            app->collision(room->mapName(), enemy, elapsedTime, true, collisionLifeInitRoutine, collisionLifeReleaseRoutine, collisionEnemyRoutine);
        }

        // Bubble ������Ʈ
        for (auto i = room->bubbles().begin(); i != room->bubbles().end(); i++)
        {
            Bubble&         bubble = *(*i);
            bubble.update(elapsedTime);
            app->collision(room->mapName(), bubble, elapsedTime, false, NULL, NULL, collisionBubbleRoutine);
        }


        // Enemy�� character�� �浹üũ
        for (int i = 0; i < room->capacity(); i++)
        {
            Client*         existed = room->client(i);
            if(existed == NULL)
                continue;

            Character&      character = *existed;
            for (auto i = room->enemies().begin(); i != room->enemies().end(); i++)
            {
                Enemy&      enemy = *(*i);

                if(character.collisionRect().contains(enemy.collisionRect()) == false)
                    continue;

                if(enemy.isPrison())
                    continue;

                character.isAlive(false);
                break;
            }
        }

        
        // Bubble�� enemy�� �浹üũ
        for(auto i = room->bubbles().begin(); i != room->bubbles().end(); i++)
        {
            Bubble&         bubble      = *(*i);
            for(auto i = room->enemies().begin(); i != room->enemies().end(); i++)
            {
                Enemy&      enemy       = *(*i);

                if(bubble.collisionRect().contains(enemy.collisionRect()) == false)
                    continue;

                if(bubble.prison(&enemy))
                    break;
            }
        }

        // Bubble�� character�� �浹üũ
        for (int i = 0; i < room->capacity(); i++)
        {
            Client*         existed = room->client(i);
            if(existed == NULL)
                continue;

            Character&      character = *existed;
            for (auto i = room->bubbles().begin(); i != room->bubbles().end(); i++)
            {
                Bubble*     bubble      = (*i);

                if(bubble->isShooting())
                    continue;

                if(character.collisionRect().contains(bubble->collisionRect()) == false)
                    continue;

                // �浹�Ǿ��µ� �� �ȿ� ���� ������ �ִٸ� ������ �׾��ٰ� �˷��ش�.
                Enemy*      enemy       = bubble->prisonEnemy();
                if(enemy != NULL)
                {
                    enemy->isAlive(false);
                    room->leave(enemy);
                }
                room->leave(bubble);

                break;
            }
        }


        // ���ӹ��� Ŭ���̾�Ʈ���� ������ json�� ��´�.
        Json::Value         users(Json::arrayValue);
        for (int i = 0; i < room->capacity(); i++)
        {
            Json::Value                     json;
            Client*                         client = room->client(i);
            if(client == NULL)
                continue;
            
            users.append(client->toJson(json));
        }

        // ���ӹ��� �������� ������ json�� ��´�.
        Json::Value             enemies(Json::arrayValue);
        for (auto i = room->enemies().begin(); i != room->enemies().end(); i++)
        {
            Json::Value                     json;
            Enemy*                          enemy = (*i);
            enemies.append(enemy->toJson(json));
        }


        // ���ӹ��� ���� ������ json�� ��´�.
        Json::Value         bubbles(Json::arrayValue);
        for (auto i = room->bubbles().begin(); i != room->bubbles().end(); i++)
        {
            Bubble*                         bubble = *i;
            Json::Value                     json;
            bubbles.append(bubble->toJson(json));
        }


        // ������ �����ߴ� json�� �����Ͽ� ������.
        Json::Value                         response;
        response["method"]                  = "update";
        response["success"]                 = true;
        response["user"]                    = users;
        response["enemies"]                 = enemies;
        response["bubbles"]                 = bubbles;
        app->sendRoom(room, response);
csection::leave("room");

        // �� ó���� �ð��� ���Ѵ�.
        int                 useTime = ::GetTickCount() - begin;

        // �ѹ� ó���ϴµ� �ɷ��� �� �ð����� �� ���� ó���ߴٸ� sleep���ش�.
        if (useTime < duration)
            Sleep(duration - useTime);

        // ���� ó���ϴµ� �ɸ� ����ð��� ��´�.
        elapsedTime                         = (::GetTickCount() - begin) / 1000.0f;
        playTime += elapsedTime;

        // begin�� �ٽ� �ʱ�ȭ
        begin                               = ::GetTickCount();
    }

    app->destroyRoom(room);
}

void App::collisionLifeInitRoutine(Map * map, Life & life, float elapsedTime, Json::Value & parameters)
{
    parameters["on ground"] = false;
    life.xMovable(true);
}

void App::collisionLifeReleaseRoutine(Map * map, Life & life, float elapsedTime, Json::Value & parameters)
{
    life.onGround(parameters["on ground"].asBool());
}

bool App::collisionLifeRoutine(Map* map, int row, int col, const rect_f & tile, Life & life, float elapsedTime, Json::Value& parameters, CollisionType collisionType)
{
    switch (collisionType)
    {
    case CollisionType::BOTTOM:
        life.xMovable(false);
        return true;

    case CollisionType::TOP:
        if (life.isJumpingUp())
            return true;

        if (row == 0)
            return true;

        parameters["on ground"] = true;
        life.position(life.xPos(), tile.top);
        return false;

    case CollisionType::RIGHT:
        life.position(tile.right + life.collisionRect().width() / 2.0f + 1e-4, life.collisionRect().bottom);
        return false;

    case CollisionType::LEFT:
        life.position(tile.left - life.collisionRect().width() / 2.0f - 1e-4, life.collisionRect().bottom);
        return false;
    }

    return false;
}

bool App::collisionCharacterRoutine(Map * map, int row, int col, const rect_f & tile, Life & life, float elapsedTime, Json::Value& parameters, CollisionType collisionType)
{
    bool                ret = collisionLifeRoutine(map, row, col, tile, life, elapsedTime, parameters, collisionType);
    switch (collisionType)
    {
    case CollisionType::BOTTOM:
        break;

    case CollisionType::LEFT:
        break;
    }

    return ret;
}

bool App::collisionEnemyRoutine(Map* map, int row, int col, const rect_f & tile, Life & life, float elapsedTime, Json::Value& parameters, CollisionType collisionType)
{
    bool                ret = collisionLifeRoutine(map, row, col, tile, life, elapsedTime, parameters, collisionType);
    Enemy&              enemy = (Enemy&)life;
    switch (collisionType)
    {
    case CollisionType::BOTTOM:
        break;

    case CollisionType::LEFT:
    case CollisionType::RIGHT:
        enemy.reverseDirection();
        break;
    }

    return ret;
}

bool App::collisionBubbleRoutine(Map* map, int row, int col, const rect_f & tile, Life & life, float elapsedTime, Json::Value& parameters, CollisionType collisionType)
{
    Bubble&                 bubble = (Bubble&)life;

    switch(collisionType)
    {
    case CollisionType::BOTTOM:
        if(bubble.isShooting())
            return false;

        bubble.position(life.xPos(), tile.bottom + life.collisionRect().height() + 1e-4);
        break;

    case CollisionType::LEFT:
        if(bubble.isShooting() == false)
            return false;

        bubble.position(tile.left - life.collisionRect().width() / 2.0f - 0.001f, life.yPos());
        bubble.isShooting(false);
        break;

    case CollisionType::RIGHT:
        if (bubble.isShooting() == false)
            return false;

        bubble.position(tile.right + life.collisionRect().width() / 2.0f + 1e-4, life.yPos());
        bubble.isShooting(false);
        break;
    }
    return false;
}

void App::stateChangeJsonRoutine(Life * sender, const std::string & name, Json::Value & value)
{
    try
    {
        value["method"] = name;
        value["id"] = sender->id();
        value["type"] = "character";
        value["success"] = true;
    }
    catch (...)
    {
        value["success"] = false;
    }
}

void App::stateChangeRoutine(Life* sender, const std::string& name, Json::Value& json)
{
    Room*                   room = sender->room();
    if (room == NULL)
        return;

    stateChangeJsonRoutine(sender, name, json);
    json["type"] = "character";
    auto framework = App::instance();
    framework->sendRoom(room, json);
}

void App::enemyStateChangeRoutine(Life* sender, const std::string& name, Json::Value& json)
{
    Room*                   room = sender->room();
    if(room == NULL)
        return;

    Enemy* enemy = (Enemy*)sender;

    stateChangeJsonRoutine(sender, name, json);
    json["type"] = "enemy";
    json["name"] = enemy->name();
    auto framework = App::instance();
    framework->sendRoom(room, json);
}

tcp* App::onConnected(tcp& socket) 
{
    return new Client(socket, this->stateChangeRoutine);
}

void App::onDisconnected(tcp& socket)
{
    Client*                 client  = (Client*)&socket;
    Room*                   room    = client->room();
    if(room != NULL)
    {
        room->leave(client);

        if (room->isEmpty())
        {
            this->_rooms.erase(room->id());
#if defined DEBUG | defined _DEBUG
            printf("%d�� ���� ����ڰ� ��� �����Ͽ����Ƿ� �ı��˴ϴ�.\n", room->id());
#endif
        }
        else
        {
            Json::Value     json;
            json["method"]          = "disconnected";
            json["id"]              = client->id();

            this->sendRoom(room, json);
        }
    }
}

bool App::onReceive(tcp& socket)
{
    //Client*                 client  = (Client*)&socket;
	bool					success = true;
	uint8_t*				buffer  = NULL;
	uint8_t*				binary  = NULL;
	uint32_t				binary_size = 0;

	// �����͸� �о����
	if(socket.recv() == false)
		return false;

	// ������ ������ �Ľ�
	istream&			istream   = socket.in_stream();
	while(true)
	{
		try
		{
			if(istream.readable_size() < sizeof(uint32_t))
				break;
			
			uint32_t size = istream.read_u32();
			if(size > istream.capacity())
				throw std::exception();

			if(istream.readable_size() < size)
				break;

			if(buffer != NULL)
				delete[] buffer;

			buffer = new uint8_t[size];
			istream.read(buffer, size);

			Json::Value root;
			Json::Reader reader;
			std::string jsons(buffer, buffer + size);
			if(reader.parse(jsons, root) == false)
				throw std::exception();

			if(root.isMember("method") == false)
				throw std::exception();
			std::string method = root["method"].asString();


			binary_size = 0;
			if(root.isMember("binary size"))
			{
				binary_size = root["binary size"].asInt();
				if(istream.readable_size() < binary_size)
					break;

				if(binary != NULL)
					delete[] binary;
				binary = new uint8_t[binary_size];
				istream.read(binary, binary_size);
			}

			this->methodEventProc((Client*)&socket, root, binary, binary_size);
		}
		catch(std::exception& e)
		{
			success = false;
			break;
		}
	}

	// ������ �������� ������� ������.
	istream.reset();

	if(buffer != NULL)
		delete[] buffer;

	if(binary != NULL)
		delete[] binary;

    return success;
}