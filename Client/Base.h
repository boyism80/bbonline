#ifndef __NETWORKSCENE_H__
#define __NETWORKSCENE_H__

#include "json/json.h"
#include "PBSocket.h"
#include "PBScene.h"
#include "PBSound.h"
#include "config.h"
using namespace PB;
using namespace PB::Windows;

class App;

namespace Scene {

class BaseScene : public scene
{
public:
    typedef bool (BaseScene::*BBPacketRoutine)(App&, Json::Value&, const Json::Value&);

private:
    std::unordered_map<std::string, BBPacketRoutine>        _eventTable;

protected:
    sound                   _sound;

public:
    BaseScene(PB::Windows::sprite* sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName, int width = GAME_SCREEN_WIDTH, int height = GAME_SCREEN_HEIGHT);
    BaseScene(const std::string& filename, PB::Windows::sprite* sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName);
    virtual ~BaseScene();

public:
    bool                    addEvent(const std::string& method, BBPacketRoutine callbackRoutine);

public:
    virtual void            onReceive(App& socket, Json::Value& response);
    virtual void            onDestroy();
};

}

#endif // !__NETWORKSCENE_H__
