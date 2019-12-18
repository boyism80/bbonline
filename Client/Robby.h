#ifndef __ROBBYSCENE_H__
#define __ROBBYSCENE_H__

#define _CRT_SECURE_NO_WARNINGS


#include "Base.h"
#include "Room.h"
#include "Map.h"

using namespace PB::Windows;

namespace Scene {

class Robby : public BaseScene
{
private:
    int                 _x, _y;
    PB::Windows::sprite _characterSprite;
    Json::Value         _rooms;

public:
    Robby(const std::string& filename, PB::Windows::sprite* sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName);
    virtual ~Robby();

private:
    window*             createRoomWindow(const Json::Value& createdRoom);
    bool                deleteRoomWindow(int id);

public:
    void                onCreate();
    void                onFrameMove(float elapsedTime);
    void                onFrameRender(dcontextable& dc, float elapsedTime);
    void                onCommand(window * control, const std::string & action, Json::Value & parameters);
    bool                onKeyboard(char vk, bool isDown);
    void                onReceive(App& app, Json::Value& root);
    void                onDestroy();

public:
    bool                roomListRoutine(App&, Json::Value&, const Json::Value&);
    bool                createRoomRoutine(App&, Json::Value&, const Json::Value&);
    bool                enterRoomRoutine(App&, Json::Value&, const Json::Value&);
    bool                leaveRoomRoutine(App&, Json::Value&, const Json::Value&);
};

}

#endif // !__ROBBYSCENE_H__
