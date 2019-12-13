#include "Object.h"

Object::Object(const point_f& position, float width, float height)
{
    this->_position         = position;
    this->_width            = width;
    this->_height           = height;

    this->_xMovable         = true;
    this->_yMovable         = true;
}

Object::~Object()
{
}

//
// collisionArea
//  충돌 범위를 얻는다.
//  오브젝트의 x, y 좌표는 left-bottom을 기준으로 한다.
//
// Parameters
//  없음
//
// Return
//  충돌 범위를 리턴
//
const rect_f Object::collisionRect() const
{
    return rect_f(this->_position.x - this->_width / 2.0f, this->_position.y - this->_height, this->_width, this->_height);
}

//
// move
//  오브젝트를 이동시킨다.
//
// Parameters
//  x       이동시킬 x값
//  y       이동시킬 y값
//
// Return
//  없음
//
void Object::move(float x, float y)
{
    this->position(this->xPos() + x, this->yPos() + y);
}

//
// position
//  현재 위치를 설정한다.
//
// Parameters
//  x       위치시킬 x값
//  y       위치시킬 y값
//
// Return
//  없음
//
void Object::position(float x, float y)
{
    if(this->_xMovable)
        this->_position.x   = x;

    if(this->_yMovable)
        this->_position.y   = y;
}

void Object::position(const point_f& point)
{
    this->position(point.x, point.y);
}

//
// position
//  현재 위치를 얻는다.
//
// Parameters
//  없음
//
// Return
//  현재 위치를 리턴
//
const point_f Object::position() const
{
    return this->_position;
}

//
// xPos
//  현재의 x 위치를 구한다.
//
// Parameters
//  없음
//
// Return
//  현재 x 위치를 리턴
//
float Object::xPos() const
{
    return this->_position.x;
}

//
// yPos
//  현재의 y 위치를 구한다.
//
// Parameters
//  없음
//
// Return
//  현재 y 위치를 리턴
//
float Object::yPos() const
{
    return this->_position.y;
}

void Object::xMovable(bool value)
{
    this->_xMovable = value;
}

void Object::yMovable(bool value)
{
    this->_yMovable = value;
}

bool Object::xMovable() const
{
    return this->_xMovable;
}

bool Object::yMovable() const
{
    return this->_yMovable;
}
