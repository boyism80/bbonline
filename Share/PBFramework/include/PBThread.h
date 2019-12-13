#ifndef __PBTHREAD_H__
#define	__PBTHREAD_H__

#include <Windows.h>
#include "PBObject.h"
#include <exception>
#include <unordered_map>

namespace PB {

class __declspec(dllexport) csection;

class __declspec(dllexport) csection_item : public virtual object
{
private:
	CRITICAL_SECTION		_criticalSection;

	friend class __declspec(dllexport) csection;

private:
	csection_item();
	csection_item(const csection_item& right);

public:
	virtual ~csection_item();

public:
	void					enter();
	void					leave();
};




class __declspec(dllexport) csection : public virtual object
{
public:
	typedef std::unordered_map<std::string, csection_item*> csection_map;

private:
	static csection*	_instance;

private:
	csection_map	_criticalSectionTable;

private:
	csection();
	virtual ~csection();

public:
	static void				init();
	static void				release();
	static void				enter(const char* format, ...);
	static bool				leave(const char* format, ...);
};




class __declspec(dllexport) thread : public virtual object
{


public:
	typedef void (*PBThreadCallbackRoutine)(thread* self);

private:
	typedef struct _STATIC_THREAD_PARAM
	{
		PBThreadCallbackRoutine		callbackRoutine;
		void*						parameter;
	} StaticThreadParam;


	friend class __declspec(dllexport) thread;
	friend DWORD WINAPI DefaultThreadRoutine(void* parameter);

private:
	PBThreadCallbackRoutine	_callback;
	HANDLE					_handle;
	void*					_parameter;

public:
	thread(PBThreadCallbackRoutine callbackFunction, void* param = NULL);
	virtual ~thread();

public:
	bool					run();
	void*					parameter() const;
	bool					wait(int timeout = INFINITE);

public:
	operator				HANDLE () const;

public:
	static bool				wait(const thread& thread, int timeout = INFINITE);

public:
	static DWORD WINAPI		DefaultThreadRoutine(void* parameter);
	static DWORD WINAPI		StaticDefaultThreadRoutine(void* parameter);
	static void				run(PBThreadCallbackRoutine callbackRoutine, void* param = NULL);
};

}

#endif // !__PBTHREAD_H__