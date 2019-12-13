#ifndef __PBPOINT_H__
#define	__PBPOINT_H__

#include <Windows.h>
#include <gdiplus.h>
#include "PBObject.h"

namespace PB { namespace Windows {

class __declspec(dllexport) point : public virtual object
{
public:
	int						x, y;

public:
	point();
	point(int x,  int y);
	point(const point& right);
	virtual ~point();

public:
	operator				POINT () const;
	operator				Gdiplus::Point() const;
};

class __declspec(dllexport) point_f : public virtual object
{
public:
	float					x, y;

public:
	point_f();
	point_f(float x, float y);
	point_f(const point& right);
	point_f(const point_f& right);
	virtual ~point_f();

public:
	operator				POINT() const;
	operator				point() const;
	operator				Gdiplus::Point() const;
	operator				Gdiplus::PointF() const;
};

} }


#endif // !__PBPOINT_H__
