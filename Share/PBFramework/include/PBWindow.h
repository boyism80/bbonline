#ifndef __PBWINDOW_H__
#define	__PBWINDOW_H__

#include "PBRect.h"
#include "PBSprite.h"
#include "PBDeviceContext.h"
#include "PBThread.h"
#include "json/json.h"
#include <array>
#include <functional>
#include <algorithm>

#ifdef _WIN64
#pragma comment(lib, "json/x64/json_vc71_libmtd.lib")
#else
#pragma comment(lib, "json/x86/json_vc71_libmtd.lib")
#endif

namespace PB { namespace Windows { namespace Control { 

//
// window
//
class __declspec(dllexport) window : public virtual object
{
private:
	bool					_isDown;

protected:
	window*					_parent;
	std::string				_id;
	char*					_spriteName;
	char*					_hoverSpriteName;
	std::string				_initialText;
	std::string				_text;
	rect					_area;
	const sprite*			_sprite;
	int						_zindex;
	std::vector<window*>	_windows;
	window*					_foregroundWindow;
	bool					_isHover;
	bool					_visible;
	int						_backgroundColor;

public:
	window(window* parent, const std::string& id, const std::string& text, int x, int y, int width, int height, const PB::Windows::sprite* sprite = NULL, const char* spriteName = NULL, const char* hoverSpriteName = NULL,
		int backgroundColor = RGB(255, 0, 255));
	window(const std::string& filename, const PB::Windows::sprite* sprite, window* parent = NULL, const char* id = NULL, int backgroundColor = RGB(255, 0, 255));
	window(const window* window, PB::Windows::Control::window* parent);
	virtual ~window();

private:
	void					hover(bool value);

protected:
	window*					gotoTop(window* window);
	bool					hover() const;

public:
	int						x() const;
	int						y() const;
	int						width() const;
	int						height() const;
	const window*			parent() const;
	const rect&				area() const;
	void					area(int x, int y, int width, int height);
	void					position(int x, int y);
	const PB::Windows::sprite* sprite() const;
	const char*				spriteName() const;
	rect					absoluteArea() const;

	const std::string&		id() const;
	const std::string&		text() const;
	void					text(const std::string& text);
	int						backgroundColor() const;

	window*					add(window* window);
	bool					remove(const std::string& id);
	window*					get(const std::string& id);
	window*					foreground() const;
	bool					foreground(window* window);
	virtual window*			copy(const PB::Windows::Control::window* window, PB::Windows::Control::window* parent = NULL);
	virtual window*			clone(window* parent = NULL);

	bool					visible() const;
	void					visible(bool value);

public:
	window*					operator [] (const std::string& id); 
	window&					operator = (const window& window);
	operator				const PB::Windows::sprite* () const;

public:
	virtual void			onCreate();
	virtual void			onFrameMove(float elapsedTime);
	virtual void			onFrameRender(dcontextable& dc, float elapsedTime);
	virtual void			onGUIRender(dcontextable& dc, float elapsedTime);
	virtual void			onCommand(window* control, const std::string& action, Json::Value& parameters);
	virtual void			onDestroy();
	virtual void			onHoverStateChanged(bool isHover);
	virtual bool			onKeyboard(char vk, bool isDown);
	virtual bool			onCharacter(wchar_t key, bool isDown);
	virtual bool			onMouse(const point& location, bool isLButtonDown, bool isRButtonDown, bool isLButtonUp, bool isRButtonUp, bool isMove);

private:
	static window*			load(std::ifstream & file, const PB::Windows::sprite* sprite, std::string* purpose, int* numChildren, window* parent = NULL);
	static window*			load(std::ifstream & file, const PB::Windows::sprite* sprite, window * parent);
};


//
// button
//
class __declspec(dllexport) button : public window
{
public:
	button(window* parent, const std::string& id, const std::string& text, int x, int y, int width, int height, const PB::Windows::sprite* sprite, const char* spriteName);
	button(const window* button, window* parent = NULL);
	virtual ~button();

public:
	virtual window*			clone(window* parent = NULL);

public:
	virtual void			onFrameMove(float elapsedTime);
	virtual void			onFrameRender(dcontextable& dc, float elapsedTime);
	virtual void			onCommand(window* control, const std::string& action, Json::Value& parameters);
	virtual void			onHoverStateChanged(bool isHover);
};


//
// textbox
//
class __declspec(dllexport) textbox : public window
{
public:
	textbox(window* parent, const std::string& id, const std::string& text, int x, int y, int width, int height, const PB::Windows::sprite* sprite, const char* spriteName);
	textbox(const window* textbox, window* parent);
	virtual ~textbox();

public:
	virtual window*			clone(window* parent);

public:
	virtual void			onFrameRender(dcontextable& dc, float elapsedTime);
	virtual bool			onKeyboard(char vk, bool isDown);
	virtual bool			onCharacter(wchar_t key, bool isDown);
};


// label
class __declspec(dllexport) label : public window
{
public:
	label(window* parent, const std::string& id, const std::string& text, int x, int y, int width, int height);
	label(const window* label, window* parent);
	virtual ~label();

public:
	virtual window*			clone(window* parent);

public:
	virtual void			onFrameRender(dcontextable& dc, float elapsedTime);
	virtual bool			onKeyboard(char vk, bool isDown);
	virtual bool			onMouse(const point& location, bool isLButtonDown, bool isRButtonDown, bool isLButtonUp, bool isRButtonUp, bool isMove);
};

} } }

#endif // !__PBWINDOW_H__
