#include "PBApplication.h"
using namespace PB::Windows;

application* application::_instance     = NULL;

//
// onCreate
//  어플리케이션 생성 이벤트 핸들러
//
// Parameters
//  없음
//
// Return
//  없음
//
void application::onCreate()
{
    dc::init();
}

//
// onDestroy
//  어플리케이션 종료 이벤트 핸들러
//
// Parameters
//  없음
//
// Return
//  없음
//
void application::onDestroy()
{
    for(auto i = this->_sceneMap.begin(); i != this->_sceneMap.end(); i++)
    {
        i->second->onDestroy();
        delete i->second;
    }

    this->_sceneMap.clear();
}

application::application(int fps, float scale) : _fps(fps), _scale(scale)
{
    this->_appInstance          = NULL;
    this->_hwnd                 = NULL;
    this->_appName              = NULL;
    this->_currentScene         = NULL;
}

application::~application()
{
    for(auto i = this->_sceneMap.begin(); i != this->_sceneMap.end(); i++)
        delete i->second;
}

//
// config
//  윈도우 폼의 속성을 설정하는 함수
//
// Parameters
//  wc      윈도우 클래스
//
// Return
//  없음
//
void application::config(WNDCLASS* wc, rect& clientRect)
{
    wc->cbClsExtra              = 0;
    wc->cbWndExtra              = 0;
    wc->hbrBackground           = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc->hCursor                 = LoadCursor(NULL, IDC_ARROW);
    wc->hIcon                   = LoadIcon(NULL, IDI_APPLICATION);
    wc->lpfnWndProc             = (WNDPROC)application::wndProc;
    wc->lpszClassName           = DEF_APP_NAME;
    wc->lpszMenuName            = NULL;
    wc->style                   = CS_HREDRAW | CS_VREDRAW;
}

//
// pushScene
//  씬을 추가한다.
//
// Parameters
//  name        씬의 이름
//  scene       씬
//
// Return
//  성공시 true, 실패시 false
//
bool application::pushScene(const std::string& name, scene* scene)
{
    if(this->_sceneMap.find(name) != this->_sceneMap.end())
        return false;

    this->_sceneMap.insert(std::make_pair(name, scene));
    return true;
}

scene * application::currentScene() const
{
    return this->_currentScene;
}

//
// trans
//  현재 보여질 씬을 바꾼다.
//
// Parameters
//  sceneNamme  씬의 이름
//
// Return
//  성공시 true, 실패시 false
//
bool application::trans(const std::string& sceneName)
{
    auto i =  this->_sceneMap.find(sceneName);
    if(i == this->_sceneMap.end())
        return false;

    if(this->_currentScene != NULL)
        this->_currentScene->onDestroy();

    this->_currentScene         = i->second;
    this->_currentScene->onCreate();
    this->resize(this->_currentScene->area());
    return true;
}

HWND application::hwnd() const
{
    return this->_hwnd;
}

rect application::windowRect() const
{
    RECT                    wndRect;
    ::GetWindowRect(this->_hwnd, &wndRect);

    return rect(wndRect);
}

rect application::clientRect() const
{
    RECT                    wndRect;
    ::GetClientRect(this->_hwnd, &wndRect);

    return rect(wndRect);
}

rect PB::Windows::application::canvasRect() const
{
    rect                    ret = this->clientRect();
    ret.right               /= this->_scale;
    ret.bottom              /= this->_scale;

    return ret;
}

void application::resize(const rect & area)
{
    rect                    wndRect(area);
    wndRect.scale(this->_scale);
    wndRect.adjustWindow(this->hwnd());
    ::SetWindowPos(this->_hwnd, NULL, wndRect.left, wndRect.top, wndRect.width(), wndRect.height(), SWP_NOMOVE);
}

bool application::fullScreen(bool use)
{
    if(use)
    {
        DEVMODE                 mode    = {0,};
        ::EnumDisplaySettings(NULL, -1, &mode);

        mode.dmPelsWidth                = 640;
        mode.dmPelsHeight               = 480;

        if(::ChangeDisplaySettings(&mode, 0) != DISP_CHANGE_SUCCESSFUL)
            return false;
    }
    else
    {
        if(::ChangeDisplaySettings(NULL, 0) != DISP_CHANGE_SUCCESSFUL)
            return false;
    }

    return true;
}

DWORD PB::Windows::application::style() const
{
    return GetWindowLong(this->_hwnd, GWL_STYLE);
}

void PB::Windows::application::style(DWORD value)
{
    ::SetWindowLong(this->_hwnd, GWL_STYLE, value);
}

float PB::Windows::application::scale() const
{
    return this->_scale;
}

void PB::Windows::application::scale(float value)
{
    this->_scale = max(1.0f, value);
}

//
// messageLoop
//  메시지 루프를 실행한다.
//
// Parameters
//  없음
//
// Return
//  모름
//
UINT application::messageLoop()
{
    MSG                     msg         = { 0, };
    float                   elapsedTime = 0;
    float                   duration    = 1000 / this->_fps;
    int                     begin       = ::GetTickCount();

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            GetMessage(&msg, NULL, 0, 0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if(this->_currentScene == NULL)
                continue;

            int             begin   = ::GetTickCount();

            this->_currentScene->onFrameMove(elapsedTime);

            dc              dc(this->_hwnd, this->_scale);
            dc_buffer       stream(dc, this->_currentScene->area());
            
            this->_currentScene->onFrameRender(stream, elapsedTime);
            this->_currentScene->onGUIRender(stream,elapsedTime);
            dc.update(stream);
            
            int             useTime = ::GetTickCount() - begin;
            if(useTime < duration)
                ::Sleep(duration - useTime);

            elapsedTime             = (::GetTickCount() - begin) / 1000.0f;
            begin                   = ::GetTickCount();
        }
    }

    return msg.wParam;
}

//
// run
//  윈폼을 실행한다.
//
// Parameters
//  instance        인스턴스 핸들
//  cmdShow         ??
//
// Return
//  없음
//
void application::run(HINSTANCE instance, int cmdShow)
{
    WNDCLASS                wc      = {0,};
    rect                    clientRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT);
    this->config(&wc, clientRect);
    ::RegisterClass(&wc);

    this->_appName                  = const_cast<char*>(wc.lpszClassName);

    this->_appInstance               = instance;
    this->_hwnd                      = CreateWindow(this->_appName, this->_appName, WS_OVERLAPPEDWINDOW,
                                                    clientRect.left, clientRect.top, clientRect.width(), clientRect.height(),
                                                    NULL, (HMENU)NULL, instance, NULL);
    
    ShowWindow(this->_hwnd, cmdShow);
    this->onCreate();
    this->messageLoop();
    this->onDestroy();
}

application * application::createInstance(application * instance)
{
    application::_instance      = instance;
    return application::instance();
}

void application::releaseInstance()
{
    delete application::_instance;
}

application* application::instance()
{
    return application::_instance;
}



//
// wndProc
//  윈도우 프로시저
//
// Parameters
//  hwnd        윈도우 핸들
//  msg         메시지
//  wparam      wparam
//  lparam      lparam
//
// Return
//  모름
//
LRESULT CALLBACK application::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    point location;

    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CHAR:
        if (application::instance()->_currentScene != NULL)
            application::instance()->_currentScene->onCharacter((wchar_t)wParam, true);
        break;

    case WM_UNICHAR:
        if(wParam != UNICODE_NOCHAR)
            return false;

        if (application::instance()->_currentScene != NULL)
            application::instance()->_currentScene->onCharacter((wchar_t)wParam, true);
        break;

    case WM_KEYDOWN:
        if(application::instance()->_currentScene != NULL)
            application::instance()->_currentScene->onKeyboard((char)wParam, true);
        break;

    case WM_KEYUP:
        if (application::instance()->_currentScene != NULL)
            application::instance()->_currentScene->onKeyboard((char)wParam, false);
        break;

    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
        if (application::instance()->_currentScene != NULL)
            application::instance()->_currentScene->onMouse(point(LOWORD(lParam) / application::instance()->scale(), HIWORD(lParam) / application::instance()->scale()), wParam & 0x0001, wParam & 0x0002, !(wParam & 0x0001), !(wParam & 0x0002), msg == WM_MOUSEMOVE);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}