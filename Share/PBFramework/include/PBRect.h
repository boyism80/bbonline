#ifndef __PBRECT_H__
#define	__PBRECT_H__

#include "PBPoint.h"

namespace PB { namespace Windows {

class __declspec(dllexport) rect : public virtual object
{
public:
	int						left,  top, right, bottom;

public:
	rect();
	rect(int x, int y, int width, int height);
	rect(const rect& right);
	rect(const RECT& right);
	virtual ~rect();

public:
	bool					contains(const point& point) const;
	bool					contains(const rect& rect) const;
	void					move(int x, int y);
	void					width(int value);
	int						width() const;
	void					height(int value);
	int						height() const;
	void					position(int x, int y);
	void					resize(int width, int height);
	void					resize(int left, int top, int right, int bottom);
	void					scale(float value);
	void					adjustWindow(HWND hwnd);
	void					adjustWindow(DWORD style, bool menu = false);
	void					adjustWindow(DWORD styleEx, DWORD style, bool menu = false);

public:
	operator				RECT() const;
	operator				Gdiplus::Rect() const;
};

class __declspec(dllexport) rect_f : public virtual object
{
public:
	float					left, top, right, bottom;

public:
	rect_f();
	rect_f(float x, float y, float width, float height);
	rect_f(const rect& right);
	rect_f(const rect_f& right);
	rect_f(const RECT& right);
	virtual ~rect_f();

public:
	bool					contains(const point_f& point) const;
	bool					contains(const rect_f& rect) const;
	void					move(float x, float y);
	void					width(float value);
	float					width() const;
	void					height(float value);
	float					height() const;
	void					position(float x, float y);
	void					resize(float width, float height);
	void					resize(float left, float top, float right, float bottom);
	void					scale(float value);
	void					adjustWindow(HWND hwnd);
	void					adjustWindow(DWORD style, bool menu = false);
	void					adjustWindow(DWORD styleEx, DWORD style, bool menu = false);

public:
	operator				RECT() const;
	operator				rect() const;
	operator				Gdiplus::Rect() const;
	operator				Gdiplus::RectF() const;
};

} }

#endif // !__PBRECT_H__
