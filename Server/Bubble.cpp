#include "Bubble.h"
#include "Character.h"
//#include "Room.h"
#include "Enemy.h"

Bubble::Bubble(Character* owner, const point_f& position, float range, bool isRight) : Life(-1, position, 20, 20, point_f(200.0f * (isRight ? 1 : -1), 0.0f), Life::Direction::Right, false), _createPoint(position)
{
    this->_owner            = owner;
    this->_range            = range;
    this->_currentRange     = 0.0f;
    this->_shotting         = true;
    this->_isRight          = isRight;
    this->_prisonEnemy      = NULL;
}

Bubble::~Bubble()
{}

Character* Bubble::owner() const
{
    return this->_owner;
}

//
// update
//  버블의 상태를 업데이트한다.
//
// Paramters
//  elapsedTime     진행 시간
//
// Return
//  없음
//
void Bubble::update(float elapsedTime)
{
    __super::update(elapsedTime);

    // 발사상태라면
    if(this->isShooting())
    {
        if(abs(this->xPos() - this->_createPoint.x) > this->_range)
            this->isShooting(false);
    }
    // 아니라면
    else
    {
        // 갇힌 적군이 있다면 위치를 강제로 맞춘다.
        if(this->_prisonEnemy != NULL)
            this->_prisonEnemy->position(this->xPos(), this->collisionRect().bottom);
    }
}

//
// prison
//  적군을 가둔다.
//
// Parametteres
//  enemy       가둘 적군
//
// Return
//  성공시 true, 실패시 false
//
bool Bubble::prison(Enemy * enemy)
{
    if(this->_prisonEnemy != NULL)
        return false;

    // 버블이 슈팅상태가 아니라면 무시
    if(this->_shotting == false)
        return false;

    // 적군이 이미 갇힌 상태라면 무시
    if(enemy->isPrison())
        return false;

    this->_prisonEnemy          = enemy;
    this->isShooting(false);
    enemy->isPrison(true);
    return true;
}

//
// prisonEnemy
//  갇힌 적을 얻는다.
//
// Parameters
//  없음
//
// Return
//  갇힌 적군. 없다면 NULL
//
Enemy * Bubble::prisonEnemy() const
{
    return this->_prisonEnemy;
}

//
// unprison
//  갇힌 적군을 풀어준다.
//
// Parameters
//  없음
//
// Return
//  갇혀있던 적군. 없다면 NULL을 리턴
//
Enemy* Bubble::unprison()
{
    Enemy*              ret     = this->_prisonEnemy;
    this->_prisonEnemy          = NULL;

    return ret;
}

//
// isShooting
//  슈팅 상태인지 판별한다.
//
// Parameters
//  없음
//
// Return
//  슈팅 상태라면 true, 아니면 false를 리턴
//
bool Bubble::isShooting() const
{
    return this->_shotting;
}

void Bubble::isShooting(bool value)
{
    this->_shotting             = value;
    
    if(value == false)
        this->velocity(0.0f, 10.0f);
}

Json::Value& Bubble::toJson(Json::Value & json)
{
    __super::toJson(json);
    json["owner"] = this->_owner->id();
    return json;
}
