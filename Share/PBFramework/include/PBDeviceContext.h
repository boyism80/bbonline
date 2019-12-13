#ifndef __PBDEVICECONTEXT_H__
#define	__PBDEVICECONTEXT_H__

#include <string>
#include <Windows.h>
#include <wingdi.h>
#include "PBSprite.h"
#include "PBRect.h"

#pragma comment(lib, "Msimg32.lib")

namespace PB { namespace Windows {

class __declspec(dllexport) dcontextable : public virtual object
{
protected:
	Graphics*				_gdip;
	HDC						_dc;

public:
	rect					_drawableRect;

protected:
	dcontextable(HDC dc);
	virtual ~dcontextable();

public:
	void					drawText(int x, int y, std::string text, int color = RGB(0, 0, 0));
	void					drawRect(const rect& rect);
	void					fillRect(const rect& rect, int color);
	bool					draw(image* image, int x, int y, bool rotateVertical = false, bool rotateHorizontal = false);
	bool					draw(image* image, const point& point, bool rotateVertical = false, bool rotateHorizontal = false);
	bool					draw(image* image, const rect& rect, bool rotateVertical = false, bool rotateHorizontal = false);
	virtual void			update(const dcontextable& src) = 0;

public:
	operator				HDC () const;

public:
	static void				init();
};

class __declspec(dllexport) dc : public dcontextable
{
private:
	HWND					_hwnd;
	float					_scale;

public:
	dc(HWND hwnd, float scale = 1.0f);
	~dc();

public:
	void					update(const dcontextable& src);
};

class __declspec(dllexport) dc_buffer : public dcontextable
{
private:
	HBITMAP					_bitmap, _beforeBitmap;
	int						_backgroundColor;

public:
	dc_buffer(dcontextable& dc, const rect& drawableRect, int backgroundColor = RGB(255, 0, 255));
	~dc_buffer();

public:
	void					update(const dcontextable& src);
};

} }

#endif // !__PBDEVICECONTEXT_H__