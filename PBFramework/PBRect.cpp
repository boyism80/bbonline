#include "PBRect.h"
using namespace PB::Windows;

rect::rect() : left(0), top(0), right(0), bottom(0)
{
}

rect::rect(int x, int y, int width, int height) : left(x), top(y), right(x + width), bottom(y + height)
{
}

rect::rect(const rect & right) : rect(right.left, right.top, right.width(), right.height())
{
}

rect::rect(const RECT & right) : rect(right.left, right.top, right.right - right.left, right.bottom - right.top)
{
}

rect::~rect()
{
}

bool rect::contains(const point & point) const
{
    if(this->left >= point.x)
        return false;

    if(this->right <= point.x)
        return false;

    if(this->top >= point.y)
        return false;

    if(this->bottom <= point.y)
        return false;

    return true;
}

bool rect::contains(const rect & rect) const
{
    if(this->contains(point(rect.left, rect.top)))
        return true;

    if(this->contains(point(rect.left, rect.bottom)))
        return true;

    if(this->contains(point(rect.right, rect.top)))
        return true;

    if(this->contains(point(rect.right, rect.bottom)))
        return true;

    return false;
}

void rect::move(int x, int y)
{
    this->left              += x;
    this->right             += x;
    this->top               += y;
    this->bottom            += y;
}

void rect::width(int value)
{
    this->right             = this->left + value;
}

int rect::width() const
{
    return this->right - this->left;
}

void rect::height(int value)
{
    this->bottom            = this->top + value;
}

int rect::height() const
{
    return this->bottom - this->top;
}

void rect::position(int x, int y)
{
    int                     oldWidth = this->width();
    int                     oldHeight = this->height();

    this->left              = x;
    this->top               = y;
    this->right             = x + oldWidth;
    this->bottom            = y + oldHeight;
}

void rect::resize(int width, int height)
{
    this->width(width);
    this->height(height);
}

void rect::resize(int left, int top, int right, int bottom)
{
    this->left          = left;
    this->top           = top;
    this->right         = right;
    this->bottom        = bottom;
}

void PB::Windows::rect::scale(float value)
{
    this->resize(this->width() * value, this->height() * value);
}

void rect::adjustWindow(HWND hwnd)
{
    RECT                rect        = *this;
    DWORD               wndStyle    = (DWORD)GetWindowLong(hwnd, GWL_STYLE);
    BOOL                useMenu     = ::GetMenu(hwnd) != NULL;
    ::AdjustWindowRect(&rect, wndStyle, useMenu);

    this->resize(rect.left, rect.top, rect.right, rect.bottom);
}

void rect::adjustWindow(DWORD style, bool menu)
{
    RECT                rect        = *this;
    ::AdjustWindowRect(&rect, style, menu);

    this->resize(rect.left, rect.top, rect.right, rect.bottom);
}

void rect::adjustWindow(DWORD styleEx, DWORD style, bool menu)
{
    RECT                rect        = *this;
    ::AdjustWindowRectEx(&rect, style, menu, styleEx);

    this->resize(rect.left, rect.top, rect.right, rect.bottom);
}

rect::operator RECT() const
{
    return RECT {this->left, this->top, this->right, this->bottom};
}

rect::operator Gdiplus::Rect() const
{
    return Gdiplus::Rect(this->left, this->top, this->width(), this->height());
}



//
// PBRectF methods
//
rect_f::rect_f() : left(0), top(0), right(0), bottom(0)
{
}

rect_f::rect_f(float x, float y, float width, float height) : left(x), top(y), right(x + width), bottom(y + height)
{
}

rect_f::rect_f(const rect & right) : rect_f(right.left, right.top, right.width(), right.height())
{
}

rect_f::rect_f(const rect_f & right) : rect_f(right.left, right.top, right.width(), right.height())
{
}

rect_f::rect_f(const RECT & right) : rect_f(right.left, right.top, right.right - right.left, right.bottom - right.top)
{
}

rect_f::~rect_f()
{
}

bool rect_f::contains(const point_f & point) const
{
    if(this->left >= point.x + 1e-4)
        return false;

    if(this->right <= point.x - 1e-4)
        return false;

    if(this->top >= point.y + 1e-4)
        return false;

    if(this->bottom <= point.y - 1e-4)
        return false;

    return true;
}

bool rect_f::contains(const rect_f & rect) const
{
    if(this->contains(point_f(rect.left, rect.top)))
        return true;

    if(this->contains(point_f(rect.left, rect.bottom)))
        return true;

    if(this->contains(point_f(rect.right, rect.top)))
        return true;

    if(this->contains(point_f(rect.right, rect.bottom)))
        return true;

    if(rect.contains(point_f(this->left, this->top)))
        return true;

    if(rect.contains(point_f(this->left, this->bottom)))
        return true;

    if(rect.contains(point_f(this->right, this->top)))
        return true;

    if(rect.contains(point_f(this->right, this->bottom)))
        return true;

    return false;
}

void rect_f::move(float x, float y)
{
    this->left              += x;
    this->right             += x;
    this->top               += y;
    this->bottom            += y;
}

void rect_f::width(float value)
{
    this->right             = this->left + value;
}

float rect_f::width() const
{
    return this->right - this->left;
}

void rect_f::height(float value)
{
    this->bottom            = this->top + value;
}

float rect_f::height() const
{
    return this->bottom - this->top;
}

void rect_f::position(float x, float y)
{
    float                   oldWidth = this->width();
    float                   oldHeight = this->height();

    this->left              = x;
    this->top               = y;
    this->right             = x + oldWidth;
    this->bottom            = y + oldHeight;
}

void rect_f::resize(float width, float height)
{
    this->width(width);
    this->height(height);
}

void rect_f::resize(float left, float top, float right, float bottom)
{
    this->left          = left;
    this->top           = top;
    this->right         = right;
    this->bottom        = bottom;
}

void PB::Windows::rect_f::scale(float value)
{
    this->resize(this->width() * value, this->height() * value);
}

void rect_f::adjustWindow(HWND hwnd)
{
    RECT                rect        = *this;
    DWORD               wndStyle    = (DWORD)GetWindowLong(hwnd, GWL_STYLE);
    BOOL                useMenu     = ::GetMenu(hwnd) != NULL;
    ::AdjustWindowRect(&rect, wndStyle, useMenu);

    this->resize(rect.left, rect.top, rect.right, rect.bottom);
}

void rect_f::adjustWindow(DWORD style, bool menu)
{
    RECT                rect        = *this;
    ::AdjustWindowRect(&rect, style, menu);

    this->resize(rect.left, rect.top, rect.right, rect.bottom);
}

void rect_f::adjustWindow(DWORD styleEx, DWORD style, bool menu)
{
    RECT                rect        = *this;
    ::AdjustWindowRectEx(&rect, style, menu, styleEx);

    this->resize(rect.left, rect.top, rect.right, rect.bottom);
}

rect_f::operator RECT() const
{
    return RECT {(int)this->left, (int)this->top, (int)this->right, (int)this->bottom};
}

rect_f::operator rect() const
{
    return rect(this->left, this->top, this->width(), this->height());
}

rect_f::operator Gdiplus::Rect() const
{
    return Gdiplus::Rect(this->left, this->top, this->width(), this->height());
}

rect_f::operator Gdiplus::RectF() const
{
    return Gdiplus::RectF(this->left, this->top, this->width(), this->height());
}
