#ifndef __PBSOUND_H__
#define	__PBSOUND_H__

#include <Windows.h>
#include <mmsystem.h>
#include <digitalv.h> 
#pragma comment(lib, "winmm.lib")

#include <string>
#include <map>

namespace PB { namespace Windows {

class __declspec(dllexport) sound
{
private:
	class element
	{
	private:
		DWORD				_deviceID;
		MCI_PLAY_PARMS		_playParams;

	public:
		element(const std::string& filename);
		~element();

	private:
		bool				load(const std::string& filename);
		void				relase();

	public:
		bool				play(bool loop = false);
		bool				pause();
		bool				stop();
	};

public:
	typedef std::map<std::string, element*> SoundDict;

private:
	SoundDict				_soundDict;

public:
	sound();
	~sound();

public:
	bool					load(const std::string& name, const std::string& filename);
	bool					play(const std::string& name, bool loop = false);
	bool					pause(const std::string& name);
	void					pause();
	bool					stop(const std::string& name);
	void					stop();
	void					clear();
};
} }

#endif // !__PBSOUND_H__
