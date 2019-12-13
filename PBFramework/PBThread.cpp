#include "PBThread.h"
using namespace PB;

thread::thread(thread::PBThreadCallbackRoutine callbackFunction, void * param)
{
    this->_handle           = NULL;
    this->_callback         = callbackFunction;
    this->_parameter        = param;
}

thread::~thread()
{
    if(this->_handle != NULL)
        ::CloseHandle(this->_handle);
}

//
// run
//  쓰레드를 시작한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
bool thread::run()
{
    this->_handle           = ::CreateThread(NULL, 0, thread::DefaultThreadRoutine, this, 0, NULL);
    return this->_handle != NULL;
}

//
// parameter
//  쓰레드로 전달된 파라미터를 얻는다.
//
// Parameters
//  없음
//
// Return
//  전달된 파라미터
//
void * thread::parameter() const
{
    return this->_parameter;
}

//
// wait
//  쓰레드가 끝날 때 까지 대기한다.
//
// Parameters
//  timeout     타임아웃
//
// Return
//  성공시 true, 실패시 false
//
bool thread::wait(int timeout)
{
    return thread::wait(*this, timeout);
}

thread::operator HANDLE() const
{
    return this->_handle;
}

//
// wait
//  쓰레드가 끝날 때 까지 대기한다.
//
// Parameters
//  thread      대기할 쓰레드
//  timeout     타임아웃
//
// Return
//  성공시 true, 실패시 false
//
bool thread::wait(const thread & thread, int timeout)
{
    return ::WaitForSingleObject(thread, timeout) != WAIT_FAILED;
}

//
// DefaultThreadRoutine
//  CreateThread 함수를 통해 전달될 쓰레드 함수 원형
//
// Parameters
//  args        인자
//
// Return
//  모름
//
DWORD thread::DefaultThreadRoutine(void * args)
{
    thread*             self = (thread*)args;
    self->_callback(self);
    return 0;
}

DWORD PB::thread::StaticDefaultThreadRoutine(void * parameter)
{
    StaticThreadParam*      staticThreadParam   = (StaticThreadParam*)parameter;
    thread              thread(staticThreadParam->callbackRoutine, staticThreadParam->parameter);

    thread._callback(&thread);

    delete staticThreadParam;
    return 0;
}

void thread::run(PBThreadCallbackRoutine callbackRoutine, void * param)
{
    StaticThreadParam*      staticThreadParam   = new StaticThreadParam();
    staticThreadParam->callbackRoutine          = callbackRoutine;
    staticThreadParam->parameter                = param;
    CloseHandle(::CreateThread(NULL, 0, thread::StaticDefaultThreadRoutine, staticThreadParam, 0, NULL));
}

csection_item::csection_item()
{
    ::InitializeCriticalSection(&this->_criticalSection);
}

csection_item::csection_item(const csection_item & right) : csection_item()
{
}

csection_item::~csection_item()
{
    DeleteCriticalSection(&this->_criticalSection);
}

//
// enter
//  임계영역에 진입한다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void csection_item::enter()
{
    ::EnterCriticalSection(&this->_criticalSection);
}

//
// leave
//  임계영역에서 빠져나온다.
//
// Parameters
//  없음
//
// Return
//  없음
//
void csection_item::leave()
{
    ::LeaveCriticalSection(&this->_criticalSection);
}


csection* csection::_instance = NULL;

csection::csection()
{
}

csection::~csection()
{
    for(std::unordered_map<std::string, csection_item*>::iterator i = this->_criticalSectionTable.begin(); i != this->_criticalSectionTable.end(); i++)
        delete i->second;
}

void csection::init()
{
    csection::_instance     = new csection();
}

void csection::release()
{
    delete csection::_instance;
}

//
// enter
//  임계영역에 진입한다.
//
// Parameters
//  id      크리티컬섹션 id
//
// Return
//  없음
//
void csection::enter(const char* format, ...)
{
    va_list                 args;
    va_start(args, format);

    char*                           id          = new char[_vscprintf(format, args) + 1];
    vsprintf(id, format, args);

    if (csection::_instance->_criticalSectionTable.find(id) == csection::_instance->_criticalSectionTable.end())
        csection::_instance->_criticalSectionTable.insert(std::make_pair(std::string(id), new csection_item()));
    
    csection::_instance->_criticalSectionTable.at(id)->enter();

    delete[] id;
    va_end(args);
}

//
// leave
//  임계영역에서 빠져나온다.
//
// Parameters
//  id      크리티컬섹션 id
//
// Return
//  없음
//
bool csection::leave(const char* format, ...)
{
    va_list                 args;
    va_start(args, format);

    char*                   id          = new char[_vscprintf(format, args) + 1];
    vsprintf(id, format, args);

    std::unordered_map<std::string, csection_item*>::iterator i = csection::_instance->_criticalSectionTable.find(id);
    if (i == csection::_instance->_criticalSectionTable.end())
        return false;

    i->second->leave();

    delete[] id;
    va_end(args);
    return true;
}