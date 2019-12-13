#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Object.h"
#include "Life.h"

class Character : public Life
{
private:
    int                     _id;

public:
    Character(int id, PB::Windows::sprite* sprite);
    Character(const Character& right);
    ~Character();

public:
    void                    onFrameMove(float elapsedTime);
    void                    onFrameRender(dcontextable& dc, float elapsedTime);

public:
    static void             onAnimationEvent(animation & animation, const std::string & actionName);
};

#endif // !__CHARACTER_H__