#include "Character.h"

Character::Character(int id, StateChangeRoutine callback) : Life(id, point_f(), 15, 20, point_f(), Direction::Right, true, callback)
{
    this->_shootDelay           = 0.0f;
    this->_shotInterval         = 0.5f;
    this->_shotRange            = 150.0f;
    this->_shotSpeed            = 300.0f;
    this->_currentRespawnTime   = 0.0f;
    this->_respawning           = false;

    this->init();
}

Character::~Character()
{
}

//
// shotBubble
//  버블을 발사한다.
//
// Parameters
//  result      성공 여부를 전달받을 값
//
// Return
//  생성된 버블
//
Bubble* Character::shotBubble()
{
    rect_f                      collisionArea = this->collisionRect();
    point_f                     shotPosition(this->direction() == Direction::Left ? collisionArea.left : collisionArea.right, this->yPos());

    // 캐릭터가 살아있는 상태가 아니라면 실패
    if (__super::isAlive() == false)
        return NULL;
    
    // 버블 발사 딜레이를 못채운 경우 실패
    if(this->_shootDelay < this->_shotInterval)
    {
        return NULL;
    }
    // 버블을 발사한다.
    // 버블을 생성한다.
    Bubble*                     bubble  = new Bubble(this, shotPosition, this->_shotRange, this->direction() == Direction::Right ? true : false);
    this->_shootDelay                   = 0.0f;
    if(this->_callback != NULL)
    {
        Json::Value json;
        json["x"] = this->xPos();
        json["y"] = this->yPos();
        this->_callback(this, "shoot", json);
    }
    
    return bubble;
}

int Character::life() const
{
    return this->_life;
}

bool Character::respawnable() const
{
    return this->_life > 0;
}

bool Character::isAlive() const
{
    return __super::isAlive();
}

void Character::isAlive(bool value)
{
    __super::isAlive(value);
    if(value == false && this->_respawning == false)
    {
        this->_life--;

        if(this->respawnable())
            this->_respawning       = true;
    }
}

bool Character::isRespawning() const
{
    return this->_currentRespawnTime != 0.0f;
}

void Character::respawnPoint(const point& point)
{
    this->_respawnPoint = point;
}

const point& Character::respawnPoint() const
{
    return this->_respawnPoint;
}

void Character::init()
{
    this->stop();
    this->_life                 = LIFE;
}

//
// update
//  캐릭터의 정보를 업데이트한다.
//
// Parameters
//  elapsedTime         진행 시간
//
// Return
//  없음
//
void Character::update(float elapsedTime)
{
    __super::update(elapsedTime);


    // 슈팅 딜레이 시간을 증가시킨다.
    this->_shootDelay           += elapsedTime;


    // 죽어있는 상태라면 리스폰 시간을 채운다.
    if(this->_respawning)
    {
        this->_currentRespawnTime       += elapsedTime;

        // 리스폰 시간을 다 채웠다면 부활시킨다.
        if(this->_currentRespawnTime > RESPAWN_TIME)
        {
            this->_respawning           = false;
            this->_currentRespawnTime   = 0;
            this->xMovable(true);
            this->yMovable(true);
            this->position(this->_respawnPoint);
            this->isAlive(true);

            if(this->_callback != NULL)
            {
                Json::Value json;
                json["x"] = this->_respawnPoint.x;
                json["y"] = this->_respawnPoint.y;
                this->_callback(this, "respawn", json);
            }
        }
    }
}

Json::Value& Character::toJson(Json::Value & json)
{
    __super::toJson(json);
    return json;
}
