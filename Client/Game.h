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
    bool                    enterRoomRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    leaveRoomRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    mapRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    generateRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    updateRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    stopRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    shotBubbleRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    enemyDieRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    clearStageRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    clearGameRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    loseGameRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    disconnectedRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    moveRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    defaultRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    jumpRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    aliveRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    shootRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    respawnRoutine(tcp&, Json::Value&, const Json::Value&);
    bool                    prisonRoutine(tcp&, Json::Value&, const Json::Value&);

public:
    static void             onAnimationEvent(animation& animation, const std::string& actionName);
};

}

#endif // !__GAMESCENE_H__