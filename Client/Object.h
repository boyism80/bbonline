#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "PBDeviceContext.h"
using namespace PB;
using namespace PB::Windows;

class Object
{
protected:
    point                   _position;

public:
    Object(int x = 0, int y = 0);
    virtual ~Object();

public:
    void                    position(int x, int y);
    int                     xPos() const;
    int                     yPos() const;
    //int                       width() const;
    //int                       height() const;
    //void                  size(int width, int height);

public:
    virtual void            onCreate();
    virtual void            onFrameMove(float elapsedTime);
    virtual void            onFrameRender(dcontextable& dc, float elapsedTime);
    virtual void            onDestroy();
//
//public:
//  operator                const rect& () const;
};

#endif // !__GAMEOBJECT_H__