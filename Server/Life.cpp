#include "Life.h"
//#include "Room.h"

static const float GRAVITY = 350.0f;        // 중력 값
static const float GRAVITY_MAX = 120.0f;    // 중력 최대 값
static const float JUMP_VEL = 160.0f;       // 점프 값

Life::Life(int id, const point_f& position, int width, int height, const point_f& velocity, Direction direction, bool isGravity, StateChangeRoutine callback) : Object(position, width, height)
{
    this->_id = id;
    this->_room = NULL;
    this->_speed = 60;
    this->_direction = direction;
    this->_jumping = false;
    this->_velocity = velocity;
    this->_isGravity = isGravity;
    this->_isAlive = true;
    this->_callback = callback;
    this->_onGround = false;
}

Life::~Life()
{}

int Life::id() const
{
    return this->_id;
}

//
// stop
//  움직임을 멈춘다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void Life::stop()
{
    this->velocity(0, this->_velocity.y);
}

//
// velocity
//  속도를 설정한다.
//
// Parameters
//  x       속도 x값
//  y       속도 y값
//
// Return
//  없음
//
void Life::velocity(float x, float y)
{
    this->_velocity.x = x;
    this->_velocity.y = y;

    auto moving = this->_velocity.x != 0.0f;
    auto direction = x > 0.0f ? Life::Direction::Right : Life::Direction::Left;
    if(x == 0.0f)
        direction = this->_direction;


    if(this->_callback != NULL && (this->_moving != moving || this->_direction != direction))
    {
        Json::Value json;
        json["state"] = moving;
        json["jumping"] = this->_jumping;
        json["direction"] = direction == Life::Direction::Left ? "left" : "right";
        this->_callback(this, "move", json);
    }

    this->_moving = moving;
    this->_direction = direction;
}

//
// velocity
//  속도를 얻는다.
//
// Parameters
//  없음
//
// Return
//  속도값을 리턴.
//
const point_f & Life::velocity() const
{
    return this->_velocity;
}

bool Life::onGround() const
{
    return this->_onGround;
}

void Life::onGround(bool value)
{
    if(this->_onGround == value)
        return;

    if(value && this->isJumpingUp())
        return;

    this->_onGround = value;
    if(this->_onGround)
    {
        this->_jumping = false;
        this->_velocity.y = 0.0f;

        if(this->_callback != NULL)
        {
            Json::Value json;
            json["state"] = false;
            json["direction"] = "down";
            json["moving"] = this->_moving;
            this->_callback(this, "jump", json);
        }
    }
}

//
// isJumping
//  점프상태인지를 판별한다.
//
// Parameters
//  없음
//
// Return
//  점프중이라면 true, 아니라면 false를 리턴
//
bool Life::isJumping() const
{
    return this->_jumping;
}

//
// isJumpingUp
//  위로 점프하는 상태인지 판별한다.
//
// Parameters
//  없음
//
// Return
//  위로 점프중이라면 true, 아니라면 false를 리턴
//
bool Life::isJumpingUp() const
{
    if (this->_jumping && this->_velocity.y > 0.0f)     // 조건 : 점프상태이면서 y축 속도가 0보다 커야 한다.
        return true;

    return false;
}

//
// isJumpingDown
//  아래로 점프하는 상태인지 판별한다.
//
// Parameters
//  없음
//
// Return
//  아래로 점프중이라면 true, 아니라면 false를 리턴
//
bool Life::isJumpingDown() const
{
    if (this->_jumping && this->_velocity.y < 0.0f)     // 조건 : 점프상태이면서 y축 속도가 0보다 작아야 한다.
        return true;

    return false;
}

//
// direction
//  바라보는 방향을 얻는다.
//
// Parameters
//  없음
//
// Return
//  바라보는 방향이 오른쪽이라면 Direction::Right
//  왼쪽이라면 Direction::Left를 리턴
//
Life::Direction Life::direction() const
{
    return this->_direction;
}

//
// speed
//  스피드를 얻는다.
//
// Parameters
//  없음
//
// Return
//  스피드를 리턴
//
int Life::speed() const
{
    return this->_speed;
}

//
// moveX
//  x축으로 이동한다.
//
// Parameters
//  direction       이동할 방향
//
// Return
//  없음
//
void Life::moveX(Life::Direction direction)
{
    this->velocity(this->_speed * (direction == Direction::Left ? -1 : 1), this->_velocity.y);
}

//
// isGraivty
//  중력의 영향을 받는지 판별한다.
//
// Parameters
//  없음
//
// Return
//  중력의 영향을 받는다면 true, 아니라면 false를 리턴
//
bool Life::isGravity() const
{
    return this->_isGravity;
}

//
// isGravity
//  중력의 영향을 받을지 설정한다.
//
// Parameters
//  value       중력의 영향을 받게 하려면 true, 아니라면 false
//
// Return
//  없음
//
void Life::isGravity(bool value)
{
    this->_isGravity        = value;
}

//
// isAlive
//  살아있는지 여부를 판별한다.
//
// Parameters
//  없음
//
// Return
//  살아있다면 true, 아니라면 false를 리턴
//
bool Life::isAlive() const
{
    return this->_isAlive;
}

//
// isAlive
//  살아있는지 여부를 설정한다.
//
// Parameters
//  value       살아있게 하려면 true, 아니라면 false
//
// Return
//  없음
//
void Life::isAlive(bool value)
{
    if(this->_isAlive == value)
        return;

    this->_isAlive          = value;
    if(this->_isAlive == false)
        this->velocity(0, 0);

    if(this->_callback != NULL)
    {
        Json::Value json;
        json["value"] = this->_isAlive;
        this->_callback(this, "alive", json);
    }
}

bool Life::entered() const
{
    return this->_room != NULL;
}

Room* Life::room() const
{
    return this->_room;
}

bool Life::room(Room* room)
{
    if(this->entered())
        return false;

    this->_room = room;
    return true;
}


bool Life::containsTile(const rect_f& collisionTileRect, const char* type, bool left, bool top, bool right, bool bottom)
{
    bool inner = strcmp(type, "inner") == 0;
    bool containsTileLeft = this->collisionRect().right - (inner ? 1e-4 : -1e-4) > collisionTileRect.left;
    bool containsTileRight = this->collisionRect().left + (inner ? 1e-4 : -1e-4) < collisionTileRect.right;
    bool containsTileTop = this->collisionRect().bottom - (inner ? 1e-4 : -1e-4) > collisionTileRect.top;
    bool containsTileBottom = this->collisionRect().top + (inner ? 1e-4 : -1e-4) < collisionTileRect.bottom;

    if(left && containsTileLeft == false)
        return false;

    if(right && containsTileRight == false)
        return false;

    if(top && containsTileTop == false)
        return false;

    if(bottom && containsTileBottom == false)
        return false;

    return true;
}

bool Life::comparePosition(const rect_f & collisionTileRect, const char * type, bool left, bool top, bool right, bool bottom)
{
    bool greater = strcmp(type, "greater") == 0;
    bool compareLeft = greater ? this->collisionRect().left > collisionTileRect.left : this->collisionRect().left < collisionTileRect.left;
    bool compareRight = greater ? this->collisionRect().right > collisionTileRect.right : this->collisionRect().right < collisionTileRect.right;
    bool compareTop = greater ? this->collisionRect().top > collisionTileRect.top : this->collisionRect().top < collisionTileRect.top;
    bool compareBottom = greater ? this->collisionRect().bottom > collisionTileRect.bottom : this->collisionRect().bottom < collisionTileRect.bottom;
    
    if(left && compareLeft == false)
        return false;

    if(right && compareRight == false)
        return false;

    if(top && compareTop == false)
        return false;

    if(bottom && compareBottom == false)
        return false;

    return true;
}

void Life::callback(StateChangeRoutine callback)
{
	this->_callback = callback;
}

//
// update
//  오브젝트의 상태를 업데이트한다.
//
// Parameters
//  elapsedTime     진행시간
//
// Return
//  없음
//
void Life::update(float elapsedTime)
{
    // 살아있지 않다면 무시
    if(this->_isAlive == false)
        return;

    // 중력의 영향을 받는다면 중력에 따른 속도를 변경한다.
    if(this->_isGravity)
    {
        auto velocity = this->_velocity;

        if(this->_onGround == false)
        {
            auto jumping = true;

            velocity.y = max(velocity.y - GRAVITY * elapsedTime, -GRAVITY_MAX);
            
            if(this->_callback != NULL)
            {
                bool fall = this->_jumping != jumping;
                bool reverse = (velocity.y <= 0 && this->_velocity.y >= 0);
                if(fall || reverse)
                {
                    Json::Value json;
                    json["direction"] = "down";
                    json["state"] = true;

                    this->_callback(this, "jump", json);
                }
            }

            this->_jumping = jumping;
        }

        this->_velocity = velocity;
    }
    this->move(this->_velocity.x * elapsedTime, -this->_velocity.y * elapsedTime);
}

//
// jump
//  점프한다.
//
// Parameters
//  velocity        점프할 속도
//
// Return
//  성공시 true, 실패시 false를 리턴
//
bool Life::jump(float velocity)
{
    // 현재 점프상태라면 무시
    if(this->_onGround == false)
        return false;

    // 속도를 변경한다.
    this->_velocity.y = JUMP_VEL;
    this->_jumping = true;

    // 공중으로 올라갈 때
    if(this->_callback != NULL)
    {
        Json::Value json;
        json["state"] = true;
        json["direction"] = "up";
        this->_callback(this, "jump", json);
    }
    return true;
}

Json::Value& Life::toJson(Json::Value & json)
{
    json["x"] = this->xPos();
    json["y"] = this->yPos();
    return json;
}
