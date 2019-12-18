#include "Enemy.h"
//#include "Room.h"

int Enemy::autoIncrementId = 0;

Enemy::Enemy(const std::string& name, const point_f& position, StateChangeRoutine callback) : Life(Enemy::autoIncrementId++, position, 15, 20, point_f(20, 0), Direction::Right, true, callback)
{
    this->_name             = name;
    this->_isPrison         = false;
}

Enemy::Enemy(const Enemy& enemy, StateChangeRoutine callback) : Enemy(enemy._name, enemy.position(), callback)
{ }

Enemy::~Enemy()
{
}

const std::string& Enemy::name() const
{
    return this->_name;
}

//
// update
//  적군의 상태를 업데이트한다.
//
// Parameters
//  elapsedTime     진행 시간
//  
// Return
//  없음
//
void Enemy::update(float elapsedTime)
{
    __super::update(elapsedTime);
}

//
// isPrison
//  갇혀있는지를 판별한다.
//
// Parameters
//  없음
//
// Return
//  갇혀있다면 true, 아니면 false를 리턴
//
bool Enemy::isPrison() const
{
    return this->_isPrison;
}

//
// isPrison
//  갇힌 상태를 설정한다.
//
// Parameters
//  value       갇힌 상태로 만드려면 true, 해제하려면 false
//
// Return
//  없음
//
void Enemy::isPrison(bool value)
{
    if(this->_isPrison == value)
        return;

    this->_isPrison         = value;
    if(this->_callback != NULL)
    {
        Json::Value json;
        json["value"] = value;
        json["x"] = this->xPos();
        json["y"] = this->yPos();
        this->_callback(this, "prison", json);
    }
}

//
// reverseDirection
//  방향을 전환한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void Enemy::reverseDirection()
{
    this->velocity(this->velocity().x * -1, this->velocity().y);
}

Json::Value& Enemy::toJson(Json::Value & json)
{
    __super::toJson(json);
    json["id"] = this->id();
    json["name"] = this->name();
    return json;
}
