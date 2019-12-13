#ifndef __GAMESERVER_H__
#define __GAMESERVER_H__

#define PORT    9997

#include "json/reader.h"
#include "Client.h"
#include "Room.h"
#include "Map.h"
#include <unordered_map>
#include <algorithm>

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

using namespace PB;

class App : public server
{
public:
    enum SendScope { ALL, ROOM, ROBBY, SELF };

    enum CollisionType {TOP, BOTTOM, LEFT, RIGHT};

public:
    typedef bool (App::*BBPacketRoutine)(Client&, const Json::Value&, Json::Value&, SendScope&);
    typedef void (*PBCollisionInitRoutine)(Map* map, Life& life, float elapsedTime, Json::Value& parameters);
    typedef bool (*PBCollisionRoutine)(Map* map, int row, int col, const rect_f& tile, Life& life, float elapsedTime, Json::Value& parameters, CollisionType collisionType);

private:
    static App*     _instance;

private:
    std::unordered_map<int, Room*>                          _rooms;
    std::unordered_map<std::string, Map*>                   _maps;
    std::unordered_map<std::string, BBPacketRoutine>        _eventTable;

private:
    App(short port);
    ~App();

private:
    bool                    loadMaps(const std::string& path);
    bool                    addEvent(const std::string& method, BBPacketRoutine callbackRoutine);
    void                    methodEventProc(Client* client, Json::Value& json);

public:
    void                    destroyRoom(Room* room);
    bool                    sendRoom(Room* room, Json::Value& json);
    bool                    sendRobby(Json::Value& json);
    bool                    sendAll(Json::Value& json);
    bool                    collision(const std::string& mapName, Life& life, float elapsedTime, bool useFlag, PBCollisionInitRoutine initRoutine, PBCollisionInitRoutine releaseRoutine, PBCollisionRoutine collisionRoutine);

public:
    static App*             instance();
    static void             release();

public:
    bool                    connectRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    disconnectRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    createRoomRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    enterRoomRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    roomListRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    standByRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    readyRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    moveRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    stopRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    mapRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    generateRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    jumpRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    shootBubbleRoutine(Client& client, const Json::Value& request, Json::Value& response, SendScope& scope);

public:
    static void             gameThreadRoutine(thread* thread);

    static void             collisionLifeInitRoutine(Map* map, Life& life, float elapsedTime, Json::Value& parameters);
    static void             collisionLifeReleaseRoutine(Map* map, Life& life, float elapsedTime, Json::Value& parameters);
    static bool             collisionLifeRoutine(Map* map, int row, int col, const rect_f& tile, Life& life, float elapsedTime, Json::Value& parameters, CollisionType collisionType);
    static bool             collisionCharacterRoutine(Map* map, int row, int col, const rect_f& tile, Life& life, float elapsedTime, Json::Value& parameters, CollisionType collisionType);
    static bool             collisionEnemyRoutine(Map* map, int row, int col, const rect_f& tile, Life& life, float elapsedTime, Json::Value& parameters, CollisionType collisionType);
    static bool             collisionBubbleRoutine(Map* map, int row, int col, const rect_f& tile, Life& life, float elapsedTime, Json::Value& parameters, CollisionType collisionType);

    static void             stateChangeJsonRoutine(Life* sender, const std::string& name, Json::Value& value);
    static void             stateChangeRoutine(Life* sender, const std::string& name, Json::Value& value);
    static void             enemyStateChangeRoutine(Life* sender, const std::string& name, Json::Value& value);

public:
    tcp*                    onConnected(tcp& socket);
    void                    onDisconnected(tcp& socket);
    bool                    onReceive(tcp& socket);
};

#endif // !__GAMESERVER_H__