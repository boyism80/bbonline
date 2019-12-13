#include "Bubble.h"

Bubble::Bubble(PB::Windows::sprite* sprite, int owner, int x, int y) : Life("Resources/animation/bubble.pba", sprite, point_f(x, y), "bubble_idle", NULL)
{
    this->_owner            = owner;
}

Bubble::~Bubble()
{
}

void Bubble::onFrameMove(float elapsedTime)
{
    __super::onFrameMove(elapsedTime);
}

void Bubble::onFrameRender(dcontextable & dc, float elapsedTime)
{
    __super::onFrameRender(dc, elapsedTime);
}