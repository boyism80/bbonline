#include "App.h"
#include "resource.h"
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

char ip[256];
int port = 0;

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hwnd, IDC_IP, "cshyeon.dlinkddns.com");
        SetDlgItemText(hwnd, IDC_PORT, "9997");
        return TRUE;

    case WM_COMMAND:
        switch(wParam)
        {
        case IDOK:
            ::GetDlgItemTextA(hwnd, IDC_IP, ip, sizeof(ip));
            port = ::GetDlgItemInt(hwnd, IDC_PORT, NULL, false);
            EndDialog(hwnd, true);
            return TRUE;

        case IDCANCEL:
            EndDialog(hwnd, false);
            return true;
        }
        break;
    }

    return FALSE;
}



int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, char* cmdParams, int cmdShow)
{
    //_CrtSetBreakAlloc(333);
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(37829);
#endif // !_DEBUG

    if(::DialogBox(instance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc) == false)
        return 0;
    
    dc::init();
    socket::init();
    csection::init();

    App*            framework = (App*)application::createInstance(new App(ip, port));
    framework->run(instance, cmdShow);
    application::releaseInstance();

    socket::release();
    csection::release();

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif // !_DEBUG
    

    return 0;
}

//
// config
//  윈도우 폼의 속성을 설정하는 이벤트 핸들러
//
// Parameters
//  wc      윈도우클래스 객체
//
// Return
//  없음
//
void App::config(WNDCLASS* wc, rect& clientRect)
{
    __super::config(wc, clientRect);
    wc->lpszClassName       = "평범한 보통팀";
}

//
// GameFramework
//  GameFramework의 생성자
//
// Parameters
//  없음
//
//
App::App(const char* ip, short port) : application(60, 1.0f), client(ip, port), _spriteGUI(L"Resources/sprite/windows.pbs"), _backgroundSprite(L"Resources/sprite/background.pbs")
{
    try
    {
        this->_character = NULL;
        if (this->connect() == false)
            throw std::exception("연결할 수 없습니다.");
    }
    catch(std::exception& e)
    {
        MessageBox(this->hwnd(), e.what(), "ERROR", MB_OK);
    }
}

App::~App()
{
    if(this->_character != NULL)
        delete this->_character;
}

//
// onCreate
//  초기화 이벤트 핸들러
//
// Parameters
//  없음
//
// Return
//  없음
//
void App::onCreate()
{
    __super::onCreate();
    //this->fullScreen(true);

    //bool ret = this->fullScreen(true);

    this->pushScene("robby", new Scene::Robby("Resources/windows/robby.pbw", &this->_spriteGUI, &this->_backgroundSprite, "robby"));
    this->pushScene("game", new Scene::Game("Resources/windows/game.pbw", &this->_spriteGUI, &this->_backgroundSprite));
    this->pushScene("stand by", new Scene::StandBy("Resources/windows/stand by.pbw", &this->_spriteGUI, &this->_backgroundSprite, "stand by"));

    this->trans("robby");
}

//
// onDestroy
//  릴리즈 이벤트 핸들러
//
// Parameters
//  없음
//
// Return
//  없음
//
void App::onDestroy()
{
    __super::onDestroy();

    Json::Value     json;
    json["method"]          = "disconnect";
    this->send(Scene::BaseScene::encodeJson(json));

    this->close();

    //this->fullScreen(false);
}

//
// onConnected
//  서버에 연결되었을 때 호출되는 이벤트 핸들러
//
// Parameters
//  sock        할당된 소켓
//
// Return
//  없음
//
void App::onConnected(tcp & sock)
{
    Json::Value             root;
    root["method"]          = "connect";
    root["success"]         = true;

    sock.send(Scene::BaseScene::encodeJson(root));
}

//
// onReceive
//  서버로부터 데이터를 받았을 때 호출되는 이벤트 핸들러
//
// Parameters
//  sock        소켓
//  bytes       받은 데이터
//
// Return
//  없음
//
bool App::onReceive(tcp & sock)
{
    std::vector<char>           buffer;
    Json::Value                 root;
    try
    {
        if(this->recv(buffer, sizeof(int)) == false)
            return false;

        int                     size    = *(int*)buffer.data();
        if(this->recv(buffer, size) == false)
            return false;

        if(Scene::BaseScene::decodeJson(buffer, root) == false)
            return false;

        std::string             method = root["method"].asString();
        if (method.compare("connect") == 0)
        {
            int                 id = root["id"].asInt();
            return true;
        }

        // 현재 씬을 얻는다.
        Scene::BaseScene*        scene = (Scene::BaseScene*)this->currentScene();
        if (scene == NULL)
            return true;


        // 현재 scene의 onReceive를 호출하면서 파싱된 json 객체를 넘겨준다.
        scene->onReceive(sock, root);
		return true;
    }
    catch(std::exception& e)
    {
        //MessageBoxA(NULL, e.what(), "", MB_OK);
		return false;
    }
}

//
// onDisconnect
//  서버로부터 연결이 끊겼을 때 호출되는 이벤트 핸들러
//
// Parameters
//  sock        소켓
//
// Return
//  없음
//
void App::onDisconnect(tcp & sock)
{
}