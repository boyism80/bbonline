#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include "Life.h"
#include "Enemy.h"

//
// Bubble
//  캐릭터가 쏘는 버블 클래스
//

class Character;

class Bubble : public Life
{
private:
    Character*              _owner;                     // 캐릭터 id
    float                   _range, _currentRange;      // 사거리, 이동한 거리
    bool                    _shotting, _isRight;        // 발사중인지 여부, 방향 (오른쪽인지)
    Enemy*                  _prisonEnemy;               // 갇힌 적군
    point_f                 _createPoint;

public:
    Bubble(Character* owner, const point_f& position, float range, bool isRight);
    ~Bubble();

public:
    Character*              owner() const;
    void                    update(float elapsedTime);
    bool                    prison(Enemy* enemy);
    Enemy*                  prisonEnemy() const;
    Enemy*                  unprison();
    bool                    isShooting() const;
    void                    isShooting(bool value);

    Json::Value&            toJson(Json::Value& json);
};

#endif // !__BUBBLE_H__