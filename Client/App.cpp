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
App::App(const char* ip, short port) : 
	application(60, 1.0f), 
	_spriteGUI(L"Resources/sprite/windows.pbs"), 
	_backgroundSprite(L"Resources/sprite/background.pbs"), 
	_character(NULL)
{
    try
    {
        //if (this->connect() == false)
        //    throw std::exception("연결할 수 없습니다.");
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

void App::send(Json::Value& json)
{
	Json::FastWriter writer;
	std::string jsons = writer.write(json);
	std::vector<char> buffer(jsons.begin(), jsons.end());

	this->_ostream.write_u32(buffer.size())
		.write(buffer.data(), buffer.size());
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
	this->send(json);

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
void App::onConnected(App & sock)
{
    Json::Value             root;
    root["method"]          = "connect";
    root["success"]         = true;

	this->send(root);
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
bool App::onReceive(App & sock)
{
    Json::Value             root;
	bool					success = true;
	uint8_t*				buffer = NULL;
	uint8_t*				binary  = NULL;

	if(this->recv() == false)
		return success;

    while(true)
	{
		try
		{
			if(this->_istream.readable_size() < sizeof(uint32_t))
				break;

			uint32_t size = this->_istream.read_u32();
			if(size > this->_istream.capacity())
				throw std::exception();

			if(buffer == NULL)
				delete[] buffer;
			buffer = new uint8_t[size];
			this->_istream.read(buffer, size);

			Json::Value root;
			Json::Reader reader;
			std::string jsons(buffer, buffer + size);
			if(reader.parse(jsons, root) == false)
				throw std::exception();

			if(root.isMember("method") == false)
				throw std::exception();
			std::string method = root["method"].asString();

			uint32_t binary_size = 0;
			if(root.isMember("binary size"))
			{
				binary_size = root["binary size"].asInt();
				if(this->_istream.readable_size() < binary_size)
					break;

				if(binary != NULL)
					delete[] binary;
				binary = new uint8_t[binary_size];
				this->_istream.read(binary, binary_size);
			}

			// 현재 씬을 얻는다.
			Scene::BaseScene*        scene = (Scene::BaseScene*)this->currentScene();
			if (scene == NULL)
				break;


			// 현재 scene의 onReceive를 호출하면서 파싱된 json 객체를 넘겨준다.
			scene->onReceive(*this, root);
			this->_istream.shift(sizeof(uint32_t) + size + binary_size);
			this->_istream.flush();
		}
		catch(std::exception& e)
		{
			//MessageBoxA(NULL, e.what(), "", MB_OK);
			success = false;
			break;
		}
	}

	this->_istream.reset();

	if(buffer != NULL)
		delete[] buffer;

	if(binary != NULL)
		delete[] binary;

	return success;
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
void App::onDisconnect(App & sock)
{
}