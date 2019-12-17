#define _CRT_SECURE_NO_WARNINGS
#include "PBLeak.h"

#ifdef _WIN64
#pragma comment(lib, "json/x64/json_vc71_libmtd.lib")
//#pragma comment(lib, "PBFramework/lib/x64/PBFramework.lib")
#else
#pragma comment(lib, "json/x86/json_vc71_libmtd.lib")
//#pragma comment(lib, "PBFramework/lib/x86/PBFramework.lib")
#endif // _WIN64

#include "PBThread.h"
#include "App.h"
#include <stdio.h>


int main(int argc, const char** argv)
{
    //new char;
    //_CrtSetBreakAlloc(1134);

    printf("port : %d\n", PORT);

    socket::init();
    csection::init();

    App* server = App::instance();
    server->execute(true);

    while(true)
    {
        char cmd;
        scanf("%c", &cmd);
        if(cmd == 'q')
            break;
    }

    server->exit();
    server->release();
    

    socket::release();
    csection::release();
    return 0;
}