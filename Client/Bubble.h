#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include "Life.h"
#include "PBSprite.h"

class Bubble : public Life
{
private:
    int                     _owner;

public:
    Bubble(PB::Windows::sprite* sprite, int owner, int x, int y);
    ~Bubble();

public:
    void                    onFrameMove(float elapsedTime);
    void                    onFrameRender(dcontextable& dc, float elapsedTime);
};

#endif // !__BUBBLE_H__
