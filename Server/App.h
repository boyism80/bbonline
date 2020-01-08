#ifndef __GAMESERVER_H__
#define __GAMESERVER_H__

#define PORT    9997

#include "session.h"
#include "acceptor.h"
#include "Room.h"
#include "Map.h"

#pragma comment(lib, "User32.lib")

using namespace PB;

class App : public base_acceptor<session>
{
public:
    enum SendScope { ALL, ROOM, ROBBY, SELF };

    enum CollisionType {TOP, BOTTOM, LEFT, RIGHT};

public:
    typedef bool (App::*BBPacketRoutine)(::session&, const Json::Value&, Json::Value&, SendScope&);
    typedef void (*PBCollisionInitRoutine)(Map* map, Life& life, float elapsedTime, Json::Value& parameters);
    typedef bool (*PBCollisionRoutine)(Map* map, int row, int col, const rect_f& tile, Life& life, float elapsedTime, Json::Value& parameters, CollisionType collisionType);

private:
    static App*     _instance;

private:
    std::map<int, Room*>							_rooms;
    std::map<std::string, Map*>						_maps;
    std::map<std::string, BBPacketRoutine>			_eventTable;
	std::thread*									_updateThread;

private:
    App(short port);
    ~App();

private:
    bool                    loadMaps(const std::string& path);
    bool                    addEvent(const std::string& method, BBPacketRoutine callbackRoutine);
    void                    methodEventProc(::session* client, Json::Value& json);

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
    bool                    connectRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    disconnectRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    createRoomRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    enterRoomRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    roomListRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    standByRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    readyRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    moveRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    stopRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    mapRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    generateRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    jumpRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);
    bool                    shootBubbleRoutine(::session& client, const Json::Value& request, Json::Value& response, SendScope& scope);

public:
    void					gameThreadRoutine();

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
	bool					handle_connected(::session& session);
	bool					handle_disconnected(::session& session);
	bool					handle_parse(::session& session);

public:
	void					handle_lose(Room* room);
	bool					handle_clear(Room* room);
	void					handle_update(Room* room, float elapsedTime);
};

#endif // !__GAMESERVER_H__