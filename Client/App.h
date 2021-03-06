#ifndef __GAMECLIENT_H__
#define __GAMECLIENT_H__

#ifdef _WIN64
#pragma comment(lib, "json/x64/json_vc71_libmtd.lib")
//#pragma comment(lib, "PBFramework/lib/x64/PBFramework.lib")
#else
#pragma comment(lib, "json/x86/json_vc71_libmtd.lib")
//#pragma comment(lib, "PBFramework/lib/x86/PBFramework.lib")
#endif // _WIN64

#include "asocket.h"
#include "json/json.h"
#include "PBApplication.h"
#include "Robby.h"
#include "Game.h"
#include "StandBy.h"
#include "Character.h"
#include "PBLeak.h"
#include "PBStream.h"

using namespace PB;
using namespace PB::Windows;

class App : public application, public ASocket
{
private:
    Character*          _character;
    std::vector<char>   _buffer;

    PB::Windows::sprite _spriteGUI, _backgroundSprite;

public:
    void                config(WNDCLASS* wc, rect& clientRect);

public:
    App(const char* ip, short port);
    ~App();

public:
	void				send(Json::Value& json);

public:
    void                onCreate();
    void                onDestroy();

public:
    void                onConnected(App& sock);
    bool                handle_receive();
    void                onDisconnect(App& sock);
};

#endif // !__GAMECLIENT_H__