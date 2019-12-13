#ifndef __PBSPRITE_H__
#define __PBSPRITE_H__

#pragma comment(lib, "Gdiplus.lib")

#include "PBObject.h"
#include <string>
#include <Windows.h>
#include <gdiplus.h>
#include <unordered_map>
#include <fstream>

using namespace Gdiplus;

namespace PB { namespace Windows {

class __declspec(dllexport) image : public virtual object
{
public:
    typedef enum _PIVOT_TAG
    {
        LeftTop = 0,
        LeftBottom = 1,
        RightTop = 2,
        RightBottom = 3,
        CenterTop = 4,
        CenterBottom = 5,
    } Pivot;

private:
    HGLOBAL                 _handle;
    Image*                  _image;
    IStream*                _stream;
    Pivot                   _pivot;

public:
    image(Pivot pivot = Pivot::CenterBottom);
    image(const wchar_t* filename, Pivot pivot = Pivot::CenterBottom);
    image(const char* bytes, int size, Pivot pivot = Pivot::CenterBottom);
    virtual ~image();

public:
    bool                    load(const wchar_t* filename);
    bool                    load(const void* bytes, int size);
    void                    rotateVertical();
    void                    rotateHorizontal();
    void                    rotate(Gdiplus::RotateFlipType rotateType);
    unsigned int            width() const;
    unsigned int            height() const;
    Pivot                   pivot() const;

public:
    operator                Image* ();
};

class __declspec(dllexport) sprite : public virtual object
{
public:
    typedef std::unordered_map<std::string, image*> image_map;

private:
    image_map               _images;

public:
    sprite(const wchar_t* filename);
    virtual ~sprite();

private:
    bool                    load(const wchar_t* filename);

public:
    image*                  get(const std::string& id) const;
    
public:
    image*                  operator [] (const std::string& id);
};

} }

#endif // !__PBSPRITE_H__