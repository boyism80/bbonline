#include "PBSound.h"
using namespace PB::Windows;

sound::element::element(const std::string& filename) : _deviceID(0xFFFFFFFF)
{
    if (this->load(filename) == false)
        throw std::exception("Cannot found file.");
}

sound::element::~element()
{
    this->relase();
}

bool sound::element::load(const std::string& filename)
{
    MCI_OPEN_PARMS      param;

    param.lpstrElementName = filename.c_str();
    param.lpstrDeviceType = "mpegvideo";
    if (::mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&param) != 0)
        return false;

    this->_deviceID = param.wDeviceID;
    return true;
}

void sound::element::relase()
{
    if (this->_deviceID == 0xFFFFFFFF)
        return;

    ::mciSendCommandW(this->_deviceID, MCI_CLOSE, 0, NULL);
}

bool sound::element::play(bool loop)
{
    if (this->_deviceID == 0xFFFFFFFF)
        return false;

    return ::mciSendCommand(this->_deviceID, MCI_PLAY, loop ? MCI_DGV_PLAY_REPEAT : MCI_NOTIFY, (DWORD)(LPVOID)&this->_playParams) == 0;
}

bool sound::element::pause()
{
    if (this->_deviceID == 0xFFFFFFFF)
        return false;

    return ::mciSendCommand(this->_deviceID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&this->_playParams) == 0;
}

bool sound::element::stop()
{
    if (this->_deviceID == 0xFFFFFFFF)
        return false;

    this->pause();
    return ::mciSendCommand(this->_deviceID, MCI_SEEK, MCI_SEEK_TO_START, 0) == 0;
}


sound::sound()
{
}

sound::~sound()
{
    this->clear();
}

bool sound::load(const std::string& name, const std::string& filename)
{
    try
    {
        this->_soundDict.insert(std::pair<std::string, sound::element*>(name, new sound::element(filename)));
        return true;
    }
    catch (std::exception&)
    {
        return false;
    }
}

bool sound::play(const std::string& name, bool loop)
{
    try
    {
        this->_soundDict[name]->play(loop);
        return true;
    }
    catch (std::exception&)
    {
        return false;
    }
}

bool sound::pause(const std::string& name)
{
    try
    {
        this->_soundDict[name]->pause();
        return true;
    }
    catch (std::exception&)
    {
        return false;
    }
}

void sound::pause()
{
    for (auto i = this->_soundDict.begin(); i != this->_soundDict.end(); i++)
    {
        try
        {
            i->second->pause();
        }
        catch (std::exception&)
        {
        }
    }
}

bool sound::stop(const std::string& name)
{
    try
    {
        this->_soundDict[name]->stop();
        return true;
    }
    catch (std::exception&)
    {
        return false;
    }
}

void sound::stop()
{
    for (auto i = this->_soundDict.begin(); i != this->_soundDict.end(); i++)
    {
        try
        {
            i->second->stop();
        }
        catch (std::exception&)
        {
        }
    }
}

void sound::clear()
{
    for (auto i = this->_soundDict.begin(); i != this->_soundDict.end(); i++)
    {
        i->second->stop();
        delete i->second;
    }

    this->_soundDict.clear();
}