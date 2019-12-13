#include"Character.h"

Character::Character(int id, PB::Windows::sprite* sprite) : Life("Resources/animation/character.pba", sprite, "idle", onAnimationEvent)
{
    this->_id           = id;
}

Character::Character(const Character & right) : Character(right._id, right.sprite())
{}

Character::~Character()
{}

void Character::onFrameMove(float elapsedTime)
{
    __super::onFrameMove(elapsedTime);
}

void Character::onFrameRender(dcontextable & dc, float elapsedTime)
{
    __super::onFrameRender(dc, elapsedTime);
}

void Character::onAnimationEvent(animation & animation, const std::string & actionName)
{
    if(actionName == "jump")
        animation.change("character");
}