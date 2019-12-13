#ifndef __PBMAP_H__
#define __PBMAP_H__

#include "PBSprite.h"
#include "PBDeviceContext.h"
#include "json/json.h"

namespace PB { namespace Windows {

class __declspec(dllexport) Map : public virtual object
{
private:
    std::string             _bgm;
    sprite*                 _sprite;
    int                     _row, _col;
    int                     _tileWidth, _tileHeight;
    std::string***          _mapTiles;

public:
    Map(sprite* sprite, const Json::Value& json);
    ~Map();

private:
    void                    parse(const Json::Value& json);
    void                    clear();

public:
    const std::string&      bgm() const;

public:
    void                    onFrameMove(float elapsedTime);
    void                    onFrameRender(dcontextable& dc, float elapsedTime);
};


} }


#endif // !__PBMAP_H__
