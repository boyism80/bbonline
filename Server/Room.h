#ifndef __ROOM_H__
#define __ROOM_H__

#define _CRT_SECURE_NO_WARNINGS

#include "session.h"
#include "Config.h"
#include "Enemy.h"
#include "Bubble.h"
#include "PBThread.h"

#define MAX_LEVEL   3

class session;

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
    session*                    _sessions[MAX_CLIENT_COUNT_IN_ROOM];
    std::vector<Enemy*>         _enemies;
    std::vector<Bubble*>        _bubbles;
    session*                    _priest;
    State                       _state;
    int                         _level;

public:
    Room(const std::string& name, session* priest, int capacity = 2);
    ~Room();

public:
    bool                        enter(session* session);
    bool                        enter(Enemy* enemy);
    bool                        enter(Bubble* bubble);
    bool                        leave(session* session);
    bool                        leave(Enemy* enemy);
    bool                        leave(Bubble* enemy);

public:
    int                         id() const;
    const std::string&          name() const;
    session*                    priest() const;
    bool                        priest(int index);
    void                        autoResetPriest();
    int                         capacity() const;
    State                       state() const;
    void                        state(Room::State value);
    session**                   sessions();
    session*                    session(int index);
    int                         sessionCount() const;
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