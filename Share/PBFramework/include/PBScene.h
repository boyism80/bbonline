#ifndef __PBSCENE_H__
#define	__PBSCENE_H__

#include "PBObject.h"
#include "PBDeviceContext.h"
#include "PBWindow.h"
#include <Windows.h>
#include <string>

namespace PB { namespace Windows {

using namespace Control;

class __declspec(dllexport) scene : public window
{
private:
	const PB::Windows::sprite*	_backgroundSprite;
	std::string					_backgroundName;

public:
	scene(PB::Windows::sprite* sprite, int width, int height, const PB::Windows::sprite* backgroundSprite, const std::string& backgroundName);
	scene(const std::string& filename, PB::Windows::sprite* sprite, const PB::Windows::sprite* backgroundSprite, const std::string& backgroundName);
	virtual ~scene();

public:
	const std::string&			backgroundName() const;
	void						backgroundName(const std::string& name);

public:
	virtual void				onFrameRender(dcontextable& dc, float elapsedTime);
};

} }

#endif // !__PBSCENE_H__