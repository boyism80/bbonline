#include "PBScene.h"
using namespace PB::Windows;
using namespace PB::Windows::Control;

PB::Windows::scene::scene(PB::Windows::sprite * sprite, int width, int height, const PB::Windows::sprite* backgroundSprite, const std::string& backgroundName) : PB::Windows::window(NULL, "", "", 0, 0, width, height, sprite),
    _backgroundSprite(backgroundSprite),
    _backgroundName(backgroundName)
{
}

PB::Windows::scene::scene(const std::string & filename, PB::Windows::sprite * sprite, const PB::Windows::sprite* backgroundSprite, const std::string& backgroundName) : PB::Windows::window(filename, sprite),
    _backgroundSprite(backgroundSprite),
    _backgroundName(backgroundName)
{
}

scene::~scene()
{
}

const std::string & PB::Windows::scene::backgroundName() const
{
    return this->_backgroundName;
}

void PB::Windows::scene::backgroundName(const std::string & name)
{
    this->_backgroundName = name;
}

void PB::Windows::scene::onFrameRender(dcontextable & dc, float elapsedTime)
{
    __super::onFrameRender(dc, elapsedTime);

    auto background = this->_backgroundSprite->get(this->_backgroundName);
    if(background != NULL)
        dc.draw(background, this->_area);
}