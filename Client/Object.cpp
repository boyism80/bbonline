#include "Object.h"

Object::Object(int x, int y) : _position(x, y)
{
    //this->_collisionArea.resize(width, height);
    //this->_collisionArea.move(x, y - height);
}

Object::~Object()
{
}

void Object::position(int x, int y)
{
    this->_position.x = x;
    this->_position.y = y;
}

int Object::xPos() const
{
    return this->_position.x;
}

int Object::yPos() const
{
    return this->_position.y;
}

void Object::onCreate()
{}

void Object::onFrameMove(float elapsedTime)
{}

void Object::onFrameRender(dcontextable& dc, float elapsedTime)
{
    //dc.drawRect(this->_collisionArea);
}

void Object::onDestroy()
{}