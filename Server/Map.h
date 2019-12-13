#ifndef __MAP_H__
#define __MAP_H__

#include "Config.h"
#include "PBObject.h"
#include <string>
#include <fstream>
#include "Enemy.h"

using namespace PB;

class Map : public virtual object
{
public:
    class Tile
    {
    public:
        typedef enum _COLLISION_FLAG_TAG
        {
            Left = 0x00000001,
            Right = 0x00000002,
            Top = 0x00000004,
            Bottom = 0x00000008,
        } CollisionFlag;

    private:
        char _id;
        char _flags;

    public:
        Tile();
        Tile(int id, int flags);
        ~Tile();

    public:
        int id() const;
        int flag() const;
    };

private:
    std::string             _bgmName;
    int                     _row, _col;
    int                     _tileWidth, _tileHeight;
    Tile***                 _mapTiles;
    point                   _respawnPoint[MAX_CLIENT_COUNT_IN_ROOM];
    std::vector<Enemy*>     _enemies;

public:
    Map(const std::string& filename);
    ~Map();

private:
    bool                    load(const std::string& filename);

public:
    const std::string&      bgm() const;
    int                     row() const;
    int                     col() const;
    int                     tileWidth() const;
    int                     tileHeight() const;
    const Tile*             get(int row, int col) const;
    const point&            respawnPoint(int index) const;
    const std::vector<Enemy*>& enemies() const;
    const rect_f            collisionRect(int row, int col);

public:
    const Tile**            operator [] (int index) const;
};

#endif // !__MAP_H__
