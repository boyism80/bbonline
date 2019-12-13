#include "Enemy.h"

Enemy::Enemy(int id, PB::Windows::sprite* sprite, std::string name, animation::animation_handler animationProc) : Life("Resources/animation/enemy.pba", sprite, name.append("_idle"), animationProc)
{
    this->_id               = id;
}

Enemy::~Enemy()
{}

int Enemy::id()
{
    return this->_id;
}
void Enemy::onFrameMove(float elapsedTime)
{
    __super::onFrameMove(elapsedTime);
}

void Enemy::onFrameRender(dcontextable& dc, float elapsedTime)
{
    __super::onFrameRender(dc, elapsedTime);
}