#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Life.h"

class Enemy : public Life
{
private:
    int                     _id;

public:
    Enemy(int id, PB::Windows::sprite* sprite, std::string name, animation::animation_handler animationProc = NULL);
    ~Enemy();

public:
    int                     id();

public:
    void                    onFrameMove(float elapsedTime);
    void                    onFrameRender(dcontextable& dc, float elapsedTime);
};

#endif // !__ENEMY_H__