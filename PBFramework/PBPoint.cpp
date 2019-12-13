#include "PBPoint.h"
using namespace PB::Windows;

point::point() : x(0), y(0)
{
}

point::point(int x, int y)  : x(x), y(y)
{}

point::point(const point & right) : point(right.x, right.y)
{
}

point::~point()
{
}

point::operator POINT() const
{
    return POINT {this->x, this->y};
}

point_f::point_f() : x(0), y(0)
{
}

point_f::point_f(float x, float y) : x(x), y(y)
{
}

point_f::point_f(const point & right) : point_f(right.x, right.y)
{
}

point_f::point_f(const point_f & right) : point_f(right.x, right.y)
{
}

point_f::~point_f()
{
}

point_f::operator POINT() const
{
    return POINT {(int)this->x, (int)this->y};
}

point_f::operator point() const
{
    return point(this->x, this->y);
}

point::operator Gdiplus::Point() const
{
    return Gdiplus::Point(this->x, this->y);
}

point_f::operator Gdiplus::PointF() const
{
    return Gdiplus::PointF(this->x, this->y);
}