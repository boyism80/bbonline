#include "Life.h"

Life::Life(const std::string & animationFilename, PB::Windows::sprite * sprite, const point_f & point, const std::string & defaultActionName, animation::animation_handler callbackProc)
    : Object(point.x, point.y),
    PB::Windows::animation(animationFilename, sprite, defaultActionName, callbackProc)
{
    this->_direction = Direction::Right;
    this->_alive = true;
}

Life::Life(const std::string & animationFilename, PB::Windows::sprite * sprite, const std::string & defaultActionName, animation::animation_handler callbackProc) : Life(animationFilename, sprite, point_f(), defaultActionName, callbackProc)
{ }

Life::~Life()
{}

void Life::direction(Direction direction)
{
    if(direction == this->_direction)
        return;

    this->_direction = direction;
}

Life::Direction Life::direction() const
{
    return this->_direction;
}

bool Life::isAlive() const
{
    return this->_alive;
}

void Life::die()
{
    this->_alive            = false;
}

void Life::onFrameMove(float elapsedTime)
{
    Object::onFrameMove(elapsedTime);
    PB::Windows::animation::onFrameMove(elapsedTime);
}

void Life::onFrameRender(dcontextable& dc, float elapsedTime)
{
    Object::onFrameRender(dc, elapsedTime);
    PB::Windows::animation::onFrameRender(dc, this->_position.x, this->_position.y, this->_direction != Direction::Right);
}