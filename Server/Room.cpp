#include "Room.h"
#include "Life.h"

Room::Room(const std::string& name, Client* priest, int capacity) : _name(name), _priest(priest), _capacity(capacity), _level(-1)
{
    static int          ROOM_INDEX = 0;     // 방이 생성될때마다 부여될 id

    this->_index        = ROOM_INDEX++;
    this->_state        = State::WAIT;

    memset(&this->_clients, NULL, sizeof(this->_clients));
}

Room::~Room()
{
csection::enter("enemies");
    for(auto i = this->_enemies.begin(); i != this->_enemies.end(); i++)
        delete *i;
csection::leave("enemies");

csection::enter("bubbles");
    for(auto i = this->_bubbles.begin(); i != this->_bubbles.end(); i++)
        delete *i;
csection::leave("bubbles");
}

//
// id
//  방의 고유 id를 얻는다.
//
// Parameters
//  없음
//
// Return
//  방의 고유 id를 리턴
//
int Room::id() const
{
    return this->_index;
}

//
// name
//  방의 이름을 얻는다.
//
// Parameters
//  없음
//
// Return
//  방의 이름을 얻는다.
//
const std::string & Room::name() const
{
    return this->_name;
}

//
// priest
//  방장의 정보를 얻는다.
//
// Parameters
//  없음
//
// Return
//  방장을 리턴
//
Client * Room::priest() const
{
    return this->_priest;
}

bool Room::priest(int index)
{
    if(index < 0 || index > this->_capacity)
        return false;

    if(this->_clients[index] == NULL)
        return false;

    this->_priest = this->_clients[index];
    return true;
}

void Room::autoResetPriest()
{
    for(int i = 0; i < this->_capacity; i++)
    {
        if(this->_clients[i] == NULL)
            continue;

        if(this->_clients[i] == this->_priest)
            continue;

        this->_priest = this->_clients[i];
        break;
    }
}

//
// Parameters
//  최대 수용 인원을 얻는다.
//
// Parameters
//  없음
//
// Return
//  게임방의 최대 수용 인원을 리턴
//
int Room::capacity() const
{
    return this->_capacity;
}

//
// state
//  게임방의 현재 상태를 얻는다.
//
// Parameters
//  없음
//
// Return
//  게임방의 현재 상태를 리턴
//
Room::State Room::state() const
{
    return this->_state;
}

void Room::state(Room::State value)
{
    this->_state = value;
}

//
// clients
//  게임방에 존재하는 클라이언트 정보를 얻는다.
//
// Parameters
//  없음
//
// Return
//  게임방에 존재하는 클라이언트 정보를 리턴
//
Client** Room::clients()
{
    return this->_clients;
}

Client* Room::client(int index)
{
    if(index < 0 || index > MAX_CLIENT_COUNT_IN_ROOM - 1)
        return NULL;

    return this->_clients[index];
}

int Room::clientCount() const
{
    int count = 0;
    for(int i = 0; i < this->_capacity; i++)
    {
        if(this->_clients[i] == NULL)
            continue;

        count++;
    }

    return count;
}

//
// enemies
//  게임방에 존재하는 적군의 정보를 얻는다.
//
// Parameterse
//  없음
//
// Return
//  게임방에 존재하는 적군의 정보를 리턴
//
std::vector<Enemy*>& Room::enemies()
{
    return this->_enemies;
}

std::vector<Bubble*>& Room::bubbles()
{
    return this->_bubbles;
}

bool Room::enter(Client * client)
{
    if(this->isFull())
        return false;

    if(this->_state != WAIT)
        return false;

    if(client->room(this) == false)
        return false;

    for(int i = 0; i < this->_capacity; i++)
    {
        if(this->_clients[i] != NULL)
            continue;

        this->_clients[i] = client;
        this->_clients[i]->order(i);
        break;
    }
    return true;
}

bool Room::enter(Enemy * enemy)
{
    if(enemy->room(this) == false)
        return false;

csection::enter("enemies");
    this->_enemies.push_back(enemy);
csection::leave("enemies");

    return true;
}

bool Room::enter(Bubble * bubble)
{
    if(bubble->room(this) == false)
        return false;

csection::enter("bubbles");
    this->_bubbles.push_back(bubble);
csection::leave("bubbles");
    
    return true;
}

bool Room::leave(Client * client)
{
    bool result = false;
csection::enter("characters");
    try
    {
        if(client->entered() == false)
            throw false;

        int order = client->order();
        if(order == -1)
            throw false;

        if(this->_priest == this->_clients[order])
            this->autoResetPriest();

        this->_clients[order]->room(NULL);
        this->_clients[order]->order(-1);
        this->_clients[order] = NULL;
        client->ready(false);
        result = true;
    }
    catch(bool e)
    {
        result = e;
    }
csection::leave("characters");

    return result;
}

bool Room::leave(Enemy * enemy)
{
    bool result = false;
csection::enter("enemies");
    try
    {
        if(enemy->entered() == false)
            throw false;

        auto i = std::find(this->_enemies.begin(), this->_enemies.end(), enemy);
        if(i == this->_enemies.end())
            throw false;

        this->_enemies.erase(i);
        delete enemy;
        result = true;
    }
    catch(bool e)
    {
        result = e;
    }
csection::leave("enemies");

    return result;
}

bool Room::leave(Bubble * bubble)
{
    bool result = false;
csection::enter("bubbles");
    try
    {
        if(bubble->entered() == false)
            throw false;

        auto i = std::find(this->_bubbles.begin(), this->_bubbles.end(), bubble);
        if(i == this->_bubbles.end())
            throw false;

        this->_bubbles.erase(i);
        delete bubble;
        result = true;
    }
    catch(bool e)
    {
        result = e;
    }
csection::leave("bubbles");

    return result;
}

//
// level
//  게임방의 현재 스테이지 레벨을 얻는다.
//
// Parameters
//  없음
//
// Return
//  게임방의 현재 스테이지 레벨을 리턴
//
int Room::level() const
{
    return this->_level;
}

//
// init
//  게임을 시작하기 전 초기화한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void Room::init()
{
    for(int i = 0; i < this->_capacity; i++)
    {
        if(this->_clients[i] == NULL)
            continue;

        Character&              character = *this->_clients[i];
        character.init();
    }
}

//
// nextLevel
//  다음 스테이지 레벨로 바꾼다.
//
// Parameters
//  없음
//
// Return
//  최대 레벨에 도달한 경우 false, 진행 가능한 경우 true를 리턴
//
bool Room::nextLevel()
{
    this->_bubbles.clear();
    for (int i = 0; i < this->_capacity; i++)
    {
        if (this->_clients[i] == NULL)
            continue;

        Character&              character = *this->_clients[i];
        character.stop();
    }

    this->_level++;
    if(this->_level < MAX_LEVEL)
        return false;

    return true;
}

//
// mapName
//  현재 사용되는 맵의 이름을 얻는다.
//
// Parameters
//  없음
//
// Return
//  현재 사용되는 맵의 이름
//
std::string Room::mapName() const
{
    char            buffer[256] = {0,};
    sprintf(buffer, "map%03d.pbm", this->_level);

    return std::string(buffer);
}

bool Room::isLose() const
{
    for (int i = 0; i < this->_capacity; i++)
    {
        if (this->_clients[i] == NULL)
            continue;

        Character&              character = *this->_clients[i];
        if(character.respawnable())
            return false;
    }

    return true;
}

bool Room::isClear() const
{
    return this->_enemies.size() == 0;
}

bool Room::isFull() const
{
    for(int i = 0; i < this->_capacity; i++)
    {
        if(this->_clients[i] == NULL)
            return false;
    }

    return true;
}

bool Room::isEmpty() const
{
    for(int i = 0; i < this->_capacity; i++)
    {
        if(this->_clients[i] != NULL)
            return false;
    }

    return true;
}

bool Room::respawn(int index, point point)
{
    if(index < 0 || index > this->_capacity - 1)
        return false;

    if(this->_clients[index] == NULL)
        return false;

    Character& character = *this->_clients[index];
    character.position(point);
    character.respawnPoint(point);
    return true;
}

void Room::destroy()
{
    for (int i = 0; i < this->_capacity; i++)
    {
        if(this->_clients[i] == NULL)
            continue;

        Room* room = this->_clients[i]->room();
        room->leave(this->_clients[i]);
    }

    memset(&this->_clients, 0, sizeof(this->_clients));
}