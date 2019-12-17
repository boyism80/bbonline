#ifndef __LIFE_H__
#define __LIFE_H__

#include "Object.h"

class Life;
class Room;
typedef void (__cdecl *StateChangeRoutine)(Life* sender, const std::string& state, Json::Value& value);

class Life : public Object
{
public:
    enum Direction { Left, Right };

private:
    int                     _id;
    int                     _speed;
    bool                    _moving;
    point_f                 _velocity;
    bool                    _jumping;
    Direction               _direction;
    bool                    _isGravity;
    bool                    _isAlive;
    bool                    _onGround;
    Room*                   _room;

protected:
    StateChangeRoutine      _callback;

    friend class Room;

protected:
    Life(int id, const point_f& position, int width, int height, const point_f& velocity = point_f(), Direction direction = Direction::Right, bool isGravity = true, StateChangeRoutine callback = NULL);

public:
    virtual ~Life();

private:
    bool                    room(Room* room);

public:
    int                     id() const;
    void                    stop();
    void                    velocity(float x, float y);
    const point_f&          velocity() const;
    bool                    onGround() const;
    void                    onGround(bool value);
    bool                    isJumping() const;
    bool                    isJumpingUp() const;
    bool                    isJumpingDown() const;
    Direction               direction() const;
    int                     speed() const;
    void                    moveX(Direction direction);
    bool                    isGravity() const;
    void                    isGravity(bool value);
    bool                    isAlive() const;
    virtual void            isAlive(bool value);
    Room*                   room() const;
    bool                    entered() const;

    bool                    containsTile(const rect_f& collisionTileRect, const char* type, bool left, bool top, bool right, bool bottom);
    bool                    comparePosition(const rect_f& collisionTileRect, const char* type, bool left, bool top, bool right, bool bottom);

	void					callback(StateChangeRoutine callback);

public:
    virtual void            update(float elapsedTime);
    virtual bool            jump(float velocity = 400.0f);
    virtual Json::Value&    toJson(Json::Value& json);
};

#endif // !__LIFEOBJECT_H__