#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#define _CRT_SECURE_NO_WARNINGS

#include "Base.h"
#include "Character.h"
#include "Map.h"
#include "Bubble.h"
#include "Enemy.h"

using namespace PB;
using namespace PB::Windows;

namespace Scene {

class Game : public BaseScene
{
public:
    typedef std::unordered_map<int, Character*> CharacterDictionary;
    typedef std::unordered_map<int, Enemy*>     EnemyDictionary;
    typedef std::vector<Bubble*>                BubbleList;

private:
    CharacterDictionary     _characters;
    EnemyDictionary         _enemies;
    BubbleList              _bubbles;
    PB::Windows::sprite     _characterSprite, _enemySprite, _mapSprite;
    Map*                    _map;
    int                     _level;

public:
    Game(const std::string& filename, PB::Windows::sprite* sprite, PB::Windows::sprite* backgroundSprite);
    virtual ~Game();

private:
    void                    clearEnemies();
    void                    clearCharacters();
    void                    clearBubbles();

public:
    void                    onCreate();
    void                    onFrameMove(float elapsedTime);
    void                    onFrameRender(dcontextable& dc, float elapsedTime);
    void                    onCommand(window * control, const std::string & action, Json::Value & parameters);
    bool                    onKeyboard(char vk, bool isDown);
    void                    onReceive(App& app, Json::Value& root);
    void                    onDestroy();

public:
    bool                    enterRoomRoutine(App&, Json::Value&, const Json::Value&);
    bool                    leaveRoomRoutine(App&, Json::Value&, const Json::Value&);
    bool                    mapRoutine(App&, Json::Value&, const Json::Value&);
    bool                    generateRoutine(App&, Json::Value&, const Json::Value&);
    bool                    updateRoutine(App&, Json::Value&, const Json::Value&);
    bool                    stopRoutine(App&, Json::Value&, const Json::Value&);
    bool                    shotBubbleRoutine(App&, Json::Value&, const Json::Value&);
    bool                    enemyDieRoutine(App&, Json::Value&, const Json::Value&);
    bool                    clearStageRoutine(App&, Json::Value&, const Json::Value&);
    bool                    clearGameRoutine(App&, Json::Value&, const Json::Value&);
    bool                    loseGameRoutine(App&, Json::Value&, const Json::Value&);
    bool                    disconnectedRoutine(App&, Json::Value&, const Json::Value&);
    bool                    moveRoutine(App&, Json::Value&, const Json::Value&);
    bool                    defaultRoutine(App&, Json::Value&, const Json::Value&);
    bool                    jumpRoutine(App&, Json::Value&, const Json::Value&);
    bool                    aliveRoutine(App&, Json::Value&, const Json::Value&);
    bool                    shootRoutine(App&, Json::Value&, const Json::Value&);
    bool                    respawnRoutine(App&, Json::Value&, const Json::Value&);
    bool                    prisonRoutine(App&, Json::Value&, const Json::Value&);

public:
    static void             onAnimationEvent(animation& animation, const std::string& actionName);
};

}

#endif // !__GAMESCENE_H__