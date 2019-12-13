#ifndef __PBLEAK_H__
#define __PBLEAK_H__

#if defined DEBUG | defined _DEBUG

#include <crtdbg.h>

static class KPULeak
{
public:
    KPULeak()
    {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    }

    ~KPULeak()
    {
        _CrtDumpMemoryLeaks();
    }
} mleak;

#endif
#endif // !__PBLEAK_H__
