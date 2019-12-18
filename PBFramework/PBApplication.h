#ifndef __PBAPPLICATION_H__
#define __PBAPPLICATION_H__

#include <Windows.h>
#include <unordered_map>
#include <string>
#include "PBScene.h"
#include "PBDeviceContext.h"
#include "PBRect.h"
#include <crtdbg.h>

#define DEF_APP_NAME    "PBApplication"



namespace PB { namespace Windows {

class __declspec(dllexport) application : public virtual object
{
    friend int APIENTRY ::WinMain(HINSTANCE instance, HINSTANCE prevInstance, char* cmdParams, int cmdShow);

private:
    static application* _instance;

public:
    typedef std::unordered_map<std::string, scene*> scene_map;

private:
    int                     _fps;
    HINSTANCE               _appInstance;       // application instance
    HWND                    _hwnd;              // window handle
    const char*             _appName;           // application name

    scene_map               _sceneMap;          // stored scenes
    scene*                  _currentScene;      // current scene

    float                   _scale;             // Display scale value

protected:
    application(int fps = 60, float scale = 1.0f);

public:
    virtual ~application();

private:
    UINT                    messageLoop();
    void                    run(HINSTANCE instance, int cmdShow);

protected:
    virtual void            config(WNDCLASS* wc, rect& clientRect);
    bool                    pushScene(const std::string& name, scene* scene);

public:
    scene*                  currentScene() const;

public:
    bool                    trans(const std::string& sceneName);
    HWND                    hwnd() const;
    rect                    windowRect() const;
    rect                    clientRect() const;
    rect                    canvasRect() const;
    void                    resize(const rect& rect);
    bool                    fullScreen(bool use);
    DWORD                   style() const;
    void                    style(DWORD value);
    float                   scale() const;
    void                    scale(float value);

public:
    virtual void            onCreate();
    virtual void            onDestroy();

    // For singleton
public:
    static application*     createInstance(application* instance);
    static void             releaseInstance();
    static application*     instance();

public:
    static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};

} }

#endif // !__PBAPPLICATION_H__