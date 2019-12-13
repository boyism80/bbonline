#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include "Life.h"
#include "Enemy.h"

//
// Bubble
//  ĳ���Ͱ� ��� ���� Ŭ����
//

class Character;

class Bubble : public Life
{
private:
    Character*              _owner;                     // ĳ���� id
    float                   _range, _currentRange;      // ��Ÿ�, �̵��� �Ÿ�
    bool                    _shotting, _isRight;        // �߻������� ����, ���� (����������)
    Enemy*                  _prisonEnemy;               // ���� ����
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