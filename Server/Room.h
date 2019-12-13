#ifndef __ROOM_H__
#define __ROOM_H__

#define _CRT_SECURE_NO_WARNINGS

#include "Config.h"
#include <vector>
#include "Client.h"
#include "Enemy.h"
#include "Bubble.h"

#define MAX_LEVEL   3

class Room
{
public:
    enum State
    {
        WAIT, GAME, RESULT,
    };

private:
    int                         _index;
    int                         _capacity;
    std::string                 _name;
    Client*                     _clients[MAX_CLIENT_COUNT_IN_ROOM];
    std::vector<Enemy*>         _enemies;
    std::vector<Bubble*>        _bubbles;
    Client*                     _priest;
    State                       _state;
    int                         _level;

public:
    Room(const std::string& name, Client* priest, int capacity = 2);
    ~Room();

public:
    bool                        enter(Client* client);
    bool                        enter(Enemy* enemy);
    bool                        enter(Bubble* bubble);
    bool                        leave(Client* client);
    bool                        leave(Enemy* enemy);
    bool                        leave(Bubble* enemy);

public:
    int                         id() const;
    const std::string&          name() const;
    Client*                     priest() const;
    bool                        priest(int index);
    void                        autoResetPriest();
    int                         capacity() const;
    State                       state() const;
    void                        state(Room::State value);
    Client**                    clients();
    Client*                     client(int index);
    int                         clientCount() const;
    std::vector<Enemy*>&        enemies();
    std::vector<Bubble*>&       bubbles();
    int                         level() const;
    void                        init();
    bool                        nextLevel();
    std::string                 mapName() const;
    
    bool                        isLose() const;
    bool                        isClear() const;
    bool                        isFull() const;
    bool                        isEmpty() const;

    bool                        respawn(int index, point point);
    void                        destroy();
};

#endif // !__ROOM_H__