#include "PBDeviceContext.h"
using namespace PB::Windows;

PB::Windows::dcontextable::dcontextable(HDC dc) : 
_dc(dc), _gdip(NULL)
{
}

PB::Windows::dcontextable::~dcontextable()
{
    if (this->_gdip != NULL)
        delete this->_gdip;
}

//
// drawText
//  텍스트를 그린다.
//
// Parameters
//  x           위치 x
//  y           위치 y
//  text        그릴 텍스트
//
// Return
//  없음
//
void dcontextable::drawText(int x, int y, std::string text, int color)
{
    int beforeTextColor = SetTextColor(*this, color);
    int beforeBackgroundMode = SetBkMode(*this, TRANSPARENT);
    TextOutA(this->_dc, x, y, text.c_str(), text.length());
    SetTextColor(*this, beforeTextColor);
    SetBkMode(*this, beforeBackgroundMode);
}

void PB::Windows::dcontextable::drawRect(const rect & rect)
{
    HBRUSH brush = (HBRUSH)::GetStockObject(NULL_BRUSH);
    HBRUSH before = (HBRUSH)SelectObject(*this, brush);
    ::Rectangle(*this, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(*this, before);
}

void PB::Windows::dcontextable::fillRect(const rect & rect, int color)
{
    RECT winRect = rect;
    HBRUSH brush = CreateSolidBrush(color);
    ::FillRect(*this, &winRect, brush);

    ::DeleteObject(brush);
}

//
// draw
//  이미지를 그린다.
//
// Parameters
//  image       그릴 이미지
//  x           위치 x
//  y           위치 y
//
// Return
//  없음
//
bool dcontextable::draw(image* image, int x, int y, bool rotateVertical, bool rotateHorizontal)
{
    auto pivot = image->pivot();
    if (pivot == image::Pivot::RightTop || pivot == image::Pivot::RightBottom)
        x -= image->width();
    else if (pivot == image::Pivot::CenterTop || pivot == image::Pivot::CenterBottom)
        x -= image->width() / 2.0f;

    if (pivot == image::Pivot::LeftBottom || pivot == pivot == image::Pivot::RightBottom || pivot == image::Pivot::CenterBottom)
        y -= image->height();

    if(image == NULL)
        return false;

    if(rotateVertical)
        image->rotateVertical();

    if(rotateHorizontal)
        image->rotateHorizontal();

    Gdiplus::Status status = this->_gdip->DrawImage((Image*)*image, x, y);

    if(rotateVertical)
        image->rotateVertical();

    if(rotateHorizontal)
        image->rotateHorizontal();

    return true;
}

bool dcontextable::draw(image * image, const point & point, bool rotateVertical, bool rotateHorizontal)
{
    return this->draw(image, point.x, point.y);
}

bool dcontextable::draw(image * image, const rect & rect, bool rotateVertical, bool rotateHorizontal)
{
    if(image == NULL)
        return false;

    if(rotateVertical)
        image->rotateVertical();

    if(rotateHorizontal)
        image->rotateHorizontal();

    Gdiplus::Status status = this->_gdip->DrawImage((Image*)*image, rect);

    if(rotateVertical)
        image->rotateVertical();

    if(rotateHorizontal)
        image->rotateHorizontal();

    return true;
}

dcontextable::operator HDC() const
{
    return this->_dc;
}

//
// init
//  GDI+ 라이브러리를 사용하기 위한 초기화를 수행한다.
//
// Parameters
//  없음
// Return
//  없음
//
void dcontextable::init()
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

PB::Windows::dc::dc(HWND hwnd, float scale) : dcontextable(::GetDC(hwnd))
{
    this->_hwnd = hwnd;
    this->_scale = scale;
    
    RECT clientRect;
    ::GetClientRect(this->_hwnd, &clientRect);
    this->_drawableRect = clientRect;
}

PB::Windows::dc::~dc()
{
    ReleaseDC(this->_hwnd, this->_dc);
}

void PB::Windows::dc::update(const dcontextable & src)
{
    ::TransparentBlt(this->_dc,
        src._drawableRect.left * this->_scale,
        src._drawableRect.top * this->_scale,
        src._drawableRect.width() * this->_scale,
        src._drawableRect.height() * this->_scale,
        src,
        src._drawableRect.left,
        src._drawableRect.top,
        src._drawableRect.width(),
        src._drawableRect.height(),
        RGB(255, 0, 255));
}

PB::Windows::dc_buffer::dc_buffer(dcontextable& dc, const rect & drawableRect, int backgroundColor) : dcontextable(::CreateCompatibleDC(dc))
{
    this->_drawableRect = drawableRect;
    this->_backgroundColor = backgroundColor;

    this->_bitmap = CreateCompatibleBitmap(dc, this->_drawableRect.width(), this->_drawableRect.height());
    this->_beforeBitmap = (HBITMAP)SelectObject(this->_dc, this->_bitmap);

    // Create graphics instance
    this->_gdip = new Graphics(this->_dc);

    // Fill white background
    RECT dcRect = rect(0, 0, this->_drawableRect.width(), this->_drawableRect.height());
    this->fillRect(dcRect, this->_backgroundColor);
}

PB::Windows::dc_buffer::~dc_buffer()
{
    if(this->_dc != NULL)
        DeleteObject(this->_dc);

    if (this->_beforeBitmap != NULL)
        SelectObject(this->_dc, this->_beforeBitmap);

    if (this->_bitmap != NULL)
        DeleteObject(this->_bitmap);
}

void PB::Windows::dc_buffer::update(const dcontextable & src)
{
    ::TransparentBlt(this->_dc,
        src._drawableRect.left,
        src._drawableRect.top,
        src._drawableRect.width(),
        src._drawableRect.height(),
        src,
        0,
        0,
        src._drawableRect.width(),
        src._drawableRect.height(),
        this->_backgroundColor);
}