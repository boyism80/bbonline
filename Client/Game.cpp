#include "Game.h"
#include "App.h"

using namespace Scene;

Game::Game(const std::string& filename, PB::Windows::sprite* sprite, PB::Windows::sprite* backgroundSprite) : BaseScene(filename, sprite, backgroundSprite, ""),
_characterSprite(L"Resources/sprite/character.pbs"),
_enemySprite(L"Resources/sprite/enemy.pbs"),
_mapSprite(L"Resources/sprite/map tiles.pbs"),
_map(NULL)
{
    this->_level = -1;

    this->addEvent("leave room", (BaseScene::BBPacketRoutine)&Game::leaveRoomRoutine);
    this->addEvent("map", (BaseScene::BBPacketRoutine)&Game::mapRoutine);
    this->addEvent("generate", (BaseScene::BBPacketRoutine)&Game::generateRoutine);
    this->addEvent("update", (BaseScene::BBPacketRoutine)&Game::updateRoutine);
    this->addEvent("stop", (BaseScene::BBPacketRoutine)&Game::stopRoutine);
    this->addEvent("shot bubble", (BaseScene::BBPacketRoutine)&Game::shotBubbleRoutine);
    this->addEvent("clear stage", (BaseScene::BBPacketRoutine)&Game::clearStageRoutine);
    this->addEvent("clear game", (BaseScene::BBPacketRoutine)&Game::clearGameRoutine);
    this->addEvent("lose game", (BaseScene::BBPacketRoutine)&Game::loseGameRoutine);
    this->addEvent("disconnected", (BaseScene::BBPacketRoutine)&Game::disconnectedRoutine);

    this->addEvent("move", (BaseScene::BBPacketRoutine)&Game::moveRoutine);
    this->addEvent("jump", (BaseScene::BBPacketRoutine)&Game::jumpRoutine);
    this->addEvent("alive", (BaseScene::BBPacketRoutine)&Game::aliveRoutine);
    this->addEvent("shoot", (BaseScene::BBPacketRoutine)&Game::shootRoutine);
    this->addEvent("respawn", (BaseScene::BBPacketRoutine)&Game::respawnRoutine);
    this->addEvent("prison", (BaseScene::BBPacketRoutine)&Game::prisonRoutine);
}

Game::~Game()
{}

//
// clearEnemies
//  적군을 초기화한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void Game::clearEnemies()
{
csection::enter("enemies");
    for (std::unordered_map<int, Enemy*>::iterator i = this->_enemies.begin(); i != this->_enemies.end(); i++)
        delete i->second;

    this->_enemies.clear();
csection::leave("enemies");
}

//
// clearCharacters
//  캐릭터들을 초기화한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void Game::clearCharacters()
{
csection::enter("characters");
    for (std::unordered_map<int, Character*>::iterator i = this->_characters.begin(); i != this->_characters.end(); i++)
        delete i->second;

    this->_characters.clear();
csection::leave("characters");
}

void Scene::Game::clearBubbles()
{
csection::enter("bubbles");
    for (auto i = this->_bubbles.begin(); i != this->_bubbles.end(); i++)
        delete *i;

    this->_bubbles.clear();
csection::leave("bubbles");
}

//
// onCreate
//  씬이 초기화될 때 호출되는 메소드
//
// Parameters
//  없음
//
// Return
//  없음
//
void Game::onCreate()
{
    __super::onCreate();
    App::instance()->scale(2.0f);

    this->_sound.load("default bgm", "Resources/sound/Default BGM.mp3");
    this->_sound.load("clear", "Resources/sound/Clear.mp3");
    this->_sound.load("game over", "Resources/sound/Game Over.mp3");
    this->_sound.load("jump", "Resources/sound/Jump.mp3");
    this->_sound.load("bubble", "Resources/sound/Bubble.mp3");
    this->_sound.load("enemy die", "Resources/sound/Enemy Die.mp3");
    this->_sound.load("character die", "Resources/sound/Character Die.mp3");



    // generate를 요청하여 인게임의 맵, 캐릭터들, 적군 기타 등등의 정보를 얻어온다.
    Json::Value             json;
    json["method"] = "generate";

    App*                    app = (App*)App::instance();
    app->send(json);
}

//
// onFrameMove
//  렌더링되기 전에 업데이트될 메소드
//
// Parameters
//  elapsedTime         진행시간
//
// Return
//  없음
//
void Game::onFrameMove(float elapsedTime)
{
    char                    mapName[256];
    sprintf(mapName, "background %03d", this->_level);
    this->backgroundName(mapName);

    __super::onFrameMove(elapsedTime);

    // 캐릭터 정보 업데이트
csection::enter("characters");
    for (std::unordered_map<int, Character*>::iterator i = this->_characters.begin(); i != this->_characters.end(); i++)
    {
        if(i->second != NULL)
            i->second->onFrameMove(elapsedTime);
    }
csection::leave("characters");

    // 적군 정보 업데이트
csection::enter("enemies");
    for (std::unordered_map<int, Enemy*>::iterator i = this->_enemies.begin(); i != this->_enemies.end(); i++)
    {
        if(i->second != NULL)
            i->second->onFrameMove(elapsedTime);
    }


    // 적군이 죽었다면 제거해준다.
    std::vector<Enemy*> deletedEnemies;
    for (std::unordered_map<int, Enemy*>::iterator i = this->_enemies.begin(); i != this->_enemies.end(); i++)
    {
        if(i->second == NULL)
            continue;

        if(i->second->isAlive())
            continue;

        deletedEnemies.push_back(i->second);
    }

    for(auto i = deletedEnemies.begin(); i != deletedEnemies.end(); i++)
    {
        Enemy* deletedEnemy = *i;
        this->_enemies.erase(deletedEnemy->id());
        delete deletedEnemy;
    }
csection::leave("enemies");

csection::enter("bubbles");
    for(auto i = this->_bubbles.begin(); i != this->_bubbles.end(); i++)
        (*i)->onFrameMove(elapsedTime);
csection::leave("bubbles");
}

//
// onFrameRender
//  렌더링 되는 메소드
//
// Parameters
//  dc              디바이스 컨텍스트
//  elapsedTime     진행시간
//
// Return
//  없음
//
void Game::onFrameRender(dcontextable & dc, float elapsedTime)
{
    __super::onFrameRender(dc, elapsedTime);

    // 배경화면을 그린다.
csection::enter("map");
    if (this->_map != NULL)
        this->_map->onFrameRender(dc, elapsedTime);
csection::leave("map");


    // 캐릭터를 그린다.
csection::enter("characters");
    for (std::unordered_map<int, Character*>::iterator i = this->_characters.begin(); i != this->_characters.end(); i++)
    {
        if(i->second != NULL)
            i->second->onFrameRender(dc, elapsedTime);
    }
csection::leave("characters");


    // 적군을 그린다.
csection::enter("enemies");
    for (std::unordered_map<int, Enemy*>::iterator i = this->_enemies.begin(); i != this->_enemies.end(); i++)
    {
        if(i->second != NULL)
            i->second->onFrameRender(dc, elapsedTime);
    }
csection::leave("enemies");

    // 버블을 그린다.
csection::enter("bubbles");
    for (std::vector<Bubble*>::iterator i = this->_bubbles.begin(); i != this->_bubbles.end(); i++)
        (*i)->onFrameRender(dc, elapsedTime);
csection::leave("bubbles");
}

void Scene::Game::onCommand(window * control, const std::string & action, Json::Value & parameters)
{
    App*                    app = (App*)App::instance();

    if(control->id().compare("yes") == 0)
    {
        Json::Value             json;
        json["method"] = "leave room";
        app->send(json);

        this->get("leave game dialog")->visible(false);
    }

    else if(control->id().compare("no") == 0)
    {
        this->get("leave game dialog")->visible(false);
    }
    
}

//
// onKeyboard
//  키 입력이 일어났을 때 호출되는 메소드
//
// Parameters
//  vk          가상키코드
//  isDown      눌렸다면 true, 떼였다면 false
//
// Return
//  없음
//
bool Game::onKeyboard(char vk, bool isDown)
{
    App*                app = (App*)App::instance();
    Json::Value         json;

    if (isDown)
    {
        switch (vk)
        {
        case VK_LEFT:
            json["method"] = "move";
            json["direction"] = "left";
            app->send(json);
            break;

        case VK_RIGHT:
            json["method"] = "move";
            json["direction"] = "right";
            app->send(json);
            break;

        case VK_UP:
            json["method"] = "jump";
            app->send(json);
            break;

        case VK_SPACE:
            json["method"] = "shot bubble";
            app->send(json);
            break;

        case VK_ESCAPE:
        case VK_BACK:
            this->get("leave game dialog")->visible(true);
            this->foreground(this->get("leave game dialog"));
            break;
        }
    }
    else
    {
        switch (vk)
        {
        case VK_LEFT:
            json["method"] = "stop";
            app->send(json);
            break;

        case VK_RIGHT:
            json["method"] = "stop";
            app->send(json);
            break;
        }
    }

    return true;
}

//
// onReceive
//  패킷을 받았을 때 호출되는 함수
//  부모의 onReceive를 호출하여 생성자에서 등록한 이벤트 핸들러가 호출되도록 한다.
//
// Parameters
//  socket          소켓
//  root            전달받은 json 객체
//
// Return
//  없음
//
void Game::onReceive(App & app, Json::Value & root)
{
    __super::onReceive(app, root);
}

void Scene::Game::onDestroy()
{
    __super::onDestroy();
csection::enter("map");
    if (this->_map != NULL)
        delete this->_map;
    this->_map = NULL;
csection::leave("map");

    this->clearEnemies();
    this->clearCharacters();
    this->clearBubbles();
}

bool Game::enterRoomRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    Json::Value             user = response["user"];
    int                     id = user["id"].asInt();

csection::enter("characters");
    if (this->_characters.find(id) != this->_characters.end())
    {

    }
    else
    {
        Character*  character = new Character(id, &this->_characterSprite);
        character->position(user["x"].asInt(), user["y"].asInt());
    }
csection::leave("characters");

    return false;
}

bool Game::leaveRoomRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    App*                    app = (App*)App::instance();
    if(response["mine"].asBool())
    {
        app->trans("robby");
    }
    else
    {
csection::enter("characters");
        this->_characters.erase(response["user"].asInt());
csection::leave("characters");
    }
    return false;
}

bool Game::mapRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
csection::enter("map");
    if (this->_map != NULL)
        delete this->_map;

    this->_map = new Map(&this->_mapSprite, request);
csection::leave("map");
    return false;
}

bool Game::generateRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    this->_level = response["level"].asInt();

csection::enter("characters");
    this->clearCharacters();

    Json::Value             users = response["user"];
    for (Json::ValueIterator i = users.begin(); i != users.end(); i++)
    {
        Json::Value         user = (*i);
        int                 id = user["id"].asInt();

        if (this->_characters.find(id) != this->_characters.end())
            delete this->_characters[id];

        Character*          character = new Character(id, &this->_characterSprite);
        character->position(user["x"].asInt(), user["y"].asInt());
        this->_characters.insert(std::make_pair(id, character));
    }
csection::leave("characters");



csection::enter("enemies");
    this->clearEnemies();
csection::leave("enemies");

csection::enter("map");
    if (this->_map != NULL)
        delete this->_map;

    this->_map = new Map(&this->_mapSprite, response["map"]);
    auto bgmName = this->_map->bgm();
    // 배경음악
    // this->_sound.play(this->_map->bgm(), true);

csection::leave("map");
    return false;
}

bool Game::updateRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
csection::enter("characters");
    Json::Value             users = response["user"];
    for (Json::ValueIterator i = users.begin(); i != users.end(); i++)
    {
        Json::Value         user = (*i);
        int                 id = user["id"].asInt();

        if (this->_characters.find(id) == this->_characters.end())
            continue;

        Character*          character = this->_characters[id];
        if(character != NULL)
            character->position(user["x"].asInt(), user["y"].asInt());
    }
csection::leave("characters");


csection::enter("enemies");
    Json::Value             enemies = response["enemies"];
    for (Json::ValueIterator i = enemies.begin(); i != enemies.end(); i++)
    {
        Json::Value         enemyJson = (*i);
        int                 id = enemyJson["id"].asInt();
        std::string         name = enemyJson["name"].asString();

        Enemy*              enemy = NULL;
        std::unordered_map<int, Enemy*>::iterator searched = this->_enemies.find(id);
        if (searched == this->_enemies.end() || searched->second == NULL)
        {
            enemy = new Enemy(id, &this->_enemySprite, name, Game::onAnimationEvent);
            //this->_enemies.insert(std::make_pair(id, enemy));
            this->_enemies[id] = enemy;
        }
        else
        {
            enemy = searched->second;
        }

        enemy->position(enemyJson["x"].asInt(), enemyJson["y"].asInt());
    }
csection::leave("enemies");


csection::enter("bubbles");

    this->clearBubbles();
    Json::Value             bubbles = response["bubbles"];

    for (Json::ValueIterator i = bubbles.begin(); i != bubbles.end(); i++)
    {
        Json::Value         bubbleJson = (*i);
        Bubble*             bubble = new Bubble(&this->_characterSprite, bubbleJson["owner"].asInt(), bubbleJson["x"].asInt(), bubbleJson["y"].asInt());
        this->_bubbles.push_back(bubble);
    }
csection::leave("bubbles");

    return false;
}

bool Game::moveRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    if(response["success"].asBool() == false)
        return false;

    const std::string&      type = response["type"].asString();
    Life::Direction         direction = response["direction"].asString().compare("left") == 0 ? Life::Direction::Left : Life::Direction::Right;
    int                     id = response["id"].asInt();
    bool                    state = response["state"].asBool();
    std::string             action;

    Life*                   life = (type == "character") ? (Life*)this->_characters[id] : (Life*)this->_enemies[id];
    if(life == NULL)
        return false;

    action = (state ? "move" : "idle");
    if(type == "enemy")
        action = response["name"].asString() + "_" + action;

    if (response["jumping"].asBool() == false)
        life->change(action);

    life->direction(direction);
    life->defaultActionName(action);
    return false;
}

bool Scene::Game::defaultRoutine(App & socket, Json::Value& request, const Json::Value& response)
{
    return false;
}

bool Scene::Game::jumpRoutine(App & socket, Json::Value& request, const Json::Value& response)
{
    int                 id = response["id"].asInt();
    const std::string&  type = response["type"].asString();
    bool                state = response["state"].asBool();
    std::string         action;

    if(state)
    {
        std::string     direction = response["direction"].asString();
        action = "jump_" + direction;

        if(direction == "up")
        {
            this->_sound.stop("jump");
            this->_sound.play("jump", false);
        }
    }

    Life* life = type == "character" ? (Life*)this->_characters[id] : (Life*)this->_enemies[id];
    if(life == NULL)
        return false;
    if(state)
        life->change(action);
    else
        life->restoreDefault();

    return false;
}

bool Scene::Game::aliveRoutine(App &, Json::Value& request, const Json::Value& response)
{
    int                 id = response["id"].asInt();
    bool                alive = response["value"].asBool();
    if(alive)
        return false;

    const std::string type = response["type"].asString();
    if(type == "character")
    {
        this->_sound.stop("character die");
        this->_sound.play("character die", false);
csection::enter("characters");
        if (this->_characters[id] != NULL)
            this->_characters[id]->change("die");
csection::leave("characters");
    }
    else
    {
        this->_sound.stop("enemy die");
        this->_sound.play("enemy die", false);
        if (this->_enemies[id] != NULL)
            this->_enemies[id]->change(response["name"].asString() + "_die");
    }

    return false;
}

bool Scene::Game::shootRoutine(App &, Json::Value& request, const Json::Value& response)
{
    int                 id = response["id"].asInt();
    this->_sound.stop("bubble");
    this->_sound.play("bubble", false);
    return false;
}

bool Scene::Game::respawnRoutine(App &, Json::Value& request, const Json::Value& response)
{
    int                 id = response["id"].asInt();
    this->_characters[id]->change("idle");
    return false;
}

bool Scene::Game::prisonRoutine(App &, Json::Value &, const Json::Value&)
{
    return false;
}

bool Game::stopRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    int                     id = response["id"].asInt();
    Character&              character = *this->_characters[id];
    

    return false;
}

bool Game::shotBubbleRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    return false;
}

bool Game::enemyDieRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    auto                i = this->_enemies.find(response["id"].asInt());
    std::string         name = response["name"].asString();

csection::enter("enemies");
    if (i != this->_enemies.end())
    {
        i->second->change(name.append("_die"));

        this->_sound.stop("enemy die");
        this->_sound.play("enemy die", false);
    }
csection::leave("enemies");

    return false;
}

bool Game::clearStageRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    request["method"] = "generate";
    return true;
}

bool Game::clearGameRoutine(App& socket, Json::Value& request, const Json::Value& response)
{
    App*                app = (App*)App::instance();
    this->_sound.stop();
    this->_sound.play("clear", false);
    ::MessageBoxA(app->hwnd(), "CLEAR", "CLEAR", MB_OK);
    app->trans("robby");

    return false;
}

bool Game::loseGameRoutine(App &, Json::Value &, const Json::Value&)
{
    App*                app = (App*)App::instance();
    this->_sound.stop("default bgm");
    this->_sound.play("game over", false);
    ::MessageBoxA(app->hwnd(), "GAME LOSE", "LOSE", MB_OK);
    app->trans("robby");

    return false;
}

bool Game::disconnectedRoutine(App &, Json::Value& request, const Json::Value& response)
{
    int                 id = response["id"].asInt();

csection::enter("characters");
    delete this->_characters[id];
    this->_characters.erase(id);
csection::leave("characters");

    return false;
}

void Game::onAnimationEvent(animation & animation, const std::string & actionName)
{
    if (actionName.find("_die") >= 0)
    {
csection::enter("enemies");
    Enemy*                  enemy = static_cast<Enemy*>(&animation);
    enemy->die();
csection::leave("enemies");
    }
}