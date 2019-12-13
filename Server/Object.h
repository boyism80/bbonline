#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "PBRect.h"
#include "json/json.h"
using namespace PB;
using namespace PB::Windows;

class Object
{
private:
    point_f                 _position;
    float                   _width, _height;
    bool                    _xMovable, _yMovable;

protected:
    Object(const point_f& position, float width, float height);
    virtual ~Object();

public:
    const rect_f            collisionRect() const;
    void                    move(float x, float y);
    void                    position(float x, float y);
    void                    position(const point_f& point);
    const point_f           position() const;
    float                   xPos() const;
    float                   yPos() const;

    void                    xMovable(bool value);
    void                    yMovable(bool value);

    bool                    xMovable() const;
    bool                    yMovable() const;
};


#endif // !__GAMEOBJECT_H__