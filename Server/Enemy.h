#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Life.h"

class Enemy : public Life
{
private:
    static int              autoIncrementId;

private:
    std::string             _name;
    bool                    _isPrison;

public:
    Enemy(const std::string& name, const point_f& position, StateChangeRoutine callback = NULL);
    Enemy(const Enemy& enemy, StateChangeRoutine callback = NULL);
    ~Enemy();

public:
    const std::string&      name() const;
    void                    update(float elapsedTime);
    bool                    isPrison() const;
    void                    isPrison(bool value);
    void                    reverseDirection();

public:
    Json::Value&            toJson(Json::Value& json);
};

#endif // !__ENEMY_H__