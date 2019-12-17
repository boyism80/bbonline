#ifndef __STAND_BY_H__
#define __STAND_BY_H__

#define _CRT_SECURE_NO_WARNINGS


#include "json/json.h"
#include "Base.h"
#include "Room.h"
#include "Map.h"

using namespace PB::Windows;

namespace Scene {

class StandBy : public BaseScene
{
private:
    Json::Value         _userList;

public:
    StandBy(const std::string& filename, PB::Windows::sprite* sprite, PB::Windows::sprite*backgroundSprite, const std::string& backgroundName);
    virtual ~StandBy();

private:
    void                updateReadyStateWindow();

public:
    void                onCreate();
    void                onFrameMove(float elapsedTime);
    void                onFrameRender(dcontextable& dc, float elapsedTime);
    void                onCommand(window * control, const std::string & action, Json::Value & parameters);
    bool                onKeyboard(char vk, bool isDown);
    void                onReceive(App& app, Json::Value& root);

public:
    bool                standByStateRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                readyRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                leaveRoomRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                disconnectedRoutine(tcp&, Json::Value&, const Json::Value&);
};

}

#endif // !__STAND_BY_H__