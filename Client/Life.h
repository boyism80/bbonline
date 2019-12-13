#ifndef __LIFEOBJECT_H__
#define __LIFEOBJECT_H__

#include "Object.h"
#include "PBAnimation.h"

class Life : public Object, public animation
{
public:
    enum Direction
    {
        Left, Right
    };

private:
    Direction               _direction;
    bool                    _alive;

protected:
    Life(const std::string& animationFilename, PB::Windows::sprite* sprite, const point_f& point, const std::string& defaultActionName = "", animation::animation_handler callbackProc = NULL);
    Life(const std::string& animationFilename, PB::Windows::sprite* sprite, const std::string& defaultActionName = "", animation::animation_handler callbackProc = NULL);
    virtual ~Life();

public:
    void                    direction(Direction direction);
    Direction               direction() const;
    bool                    isAlive() const;
    void                    die();

    virtual void            onFrameMove(float elapsedTime);
    virtual void            onFrameRender(dcontextable& dc, float elapsedTime);
};

#endif // !__LIFEOBJECT_H__
