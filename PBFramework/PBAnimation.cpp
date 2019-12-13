#include "PBAnimation.h"
using namespace PB;
using namespace PB::Windows;

animate_frame::animate_frame(const std::string & name, int x, int y, float duration)
{
    this->_name             = name;
    this->_x                = x;
    this->_y                = y;
    this->_duration         = duration;
}

animate_frame::~animate_frame()
{
}

float animate_frame::duration() const
{
    return this->_duration;
}

int animate_frame::x() const
{
    return this->_x;
}

int animate_frame::y() const
{
    return this->_y;
}

const std::string & animate_frame::name() const
{
    return this->_name;
}






animate_action::animate_action(bool isLoop)
{
    this->_isLoop           = isLoop;
    this->_current          = 0;
    this->_elapsedTime      = 0.0;
}

animate_action::~animate_action()
{
    for (std::vector<animate_frame*>::iterator i = this->_animateFrames.begin(); i != this->_animateFrames.end(); i++)
        delete (*i);
}

void animate_action::addFrame(animate_frame* animateFrame)
{
    this->_animateFrames.push_back(animateFrame);
}

bool animate_action::next()
{
    if(this->_current + 1 > this->_animateFrames.size() - 1)
    {
        if(this->_isLoop)
            this->_current  = 0;
        else
            return false;
    }
    else
    {
        this->_current++;
    }

    return true;
}

float animate_action::duration() const
{
    float                   ret = 0;
    for(std::vector<animate_frame*>::const_iterator i = this->_animateFrames.begin(); i != this->_animateFrames.end(); i++)
        ret                 += (*i)->duration();

    return ret;
}

const animate_frame & animate_action::currentFrame() const
{
    return *this->_animateFrames.at(this->_current);
}

void animate_action::reset()
{
    this->_current                      = 0;
    this->_elapsedTime                  = 0.0f;
}

bool animate_action::onFrameMove(float elapsedTime)
{
    const animate_frame&        animate_frame   = this->currentFrame();
    if(animate_frame.duration() < this->_elapsedTime)
    {
        this->_elapsedTime              = 0;
        return this->next();
    }
    else
    {
        this->_elapsedTime              += elapsedTime;
        return true;
    }
}

void animate_action::onFrameRender(dcontextable & dc, sprite * sprite, int x, int y, bool rotateVertical)
{
    const animate_frame&        current = this->currentFrame();
    image*                      image   = sprite->get(current.name());

    dc.draw(image, x + current.x(), y + current.y(), rotateVertical);
}


animation::animation(const std::string & filename, PB::Windows::sprite * sprite, const std::string& defaultActionName, animation::animation_handler callbackProc)
{
    this->_sprite               = sprite;
    this->_isRunning            = true;
    this->_defaultActionName    = defaultActionName;
    this->_currentActionName    = defaultActionName;
    this->_currentAction        = NULL;
    this->_callbackProc         = callbackProc;

    this->load(filename);
    this->change(this->_currentActionName);
}

animation::~animation()
{
    for (auto i = this->_animateActions.begin(); i != this->_animateActions.end(); i++)
        delete i->second;

    this->_animateActions.clear();
    this->_currentAction = NULL;
}

bool animation::load(const std::string & filename)
{
    try
    {
        std::ifstream           file(filename, std::ios::binary);
        if(file.is_open() == false)
            throw std::exception("Cannot find file");

        int                     actionCount         = 0;
        file.read((char*)&actionCount, sizeof(int));

        for(int i1 = 0; i1 < actionCount; i1++)
        {
            char                actionNameLength    = 0;
            file.read(&actionNameLength, sizeof(char));

            char*               actionName          = new char[actionNameLength + 1];
            file.read(actionName, actionNameLength);
            actionName[actionNameLength]            = 0;

            bool                isLoop;
            file.read((char*)&isLoop, sizeof(bool));

            animate_action* action              = new animate_action(isLoop);
            this->_animateActions.insert(std::make_pair(actionName, action));


            int                 frameCount = 0;
            file.read((char*)&frameCount, sizeof(int));

            for (int i2 = 0; i2 < frameCount; i2++)
            {
                char            frameNameLength;
                file.read(&frameNameLength, sizeof(char));

                char*           frameName           = new char[frameNameLength + 1];
                file.read(frameName, frameNameLength);
                frameName[frameNameLength]          = 0;

                float           duration;
                file.read((char*)&duration, sizeof(float));

                int             x, y;
                file.read((char*)&x, sizeof(int));
                file.read((char*)&y, sizeof(int));

                action->addFrame(new animate_frame(frameName, x, y, duration));
                
                // Release animate frame memory
                delete[] frameName;
            }

            // Release animate action memory
            delete[] actionName;
        }

        return true;
    }
    catch(std::exception&)
    {}

    return false;
}

bool animation::change(const std::string & actionName)
{
    animation::action_map::iterator i = this->_animateActions.find(actionName);
    if(i == this->_animateActions.end())
        return false;

    if(this->_currentAction != NULL && this->_currentActionName != actionName)
        this->_currentAction->reset();

    this->_previousActionName       = this->_currentActionName;
    this->_currentActionName        = i->first;
    this->_currentAction            = i->second;
    return true;
}

void PB::Windows::animation::defaultActionName(const std::string & name)
{
    this->_defaultActionName        = name;
}

const std::string & PB::Windows::animation::defaultActionName() const
{
    return this->_defaultActionName;
}

void animation::stop()
{
    this->_isRunning        = false;
}

void animation::resume()
{
    this->_isRunning        = true;
}

sprite* animation::sprite() const
{
    return this->_sprite;
}

int PB::Windows::animation::currentWidth() const
{
    if(this->_currentAction == NULL)
        return -1;

    const std::string&      name    = this->_currentAction->currentFrame().name();
    return this->_sprite->get(name)->width();
}

int PB::Windows::animation::currentHeight() const
{
    if(this->_currentAction == NULL)
        return -1;

    const std::string&      name    = this->_currentAction->currentFrame().name();
    return this->_sprite->get(name)->height();
}

void PB::Windows::animation::restoreDefault()
{
    this->change(this->_defaultActionName);
}

void PB::Windows::animation::restorePrevious()
{
    this->change(this->_previousActionName);
}

void animation::onFrameMove(float elapsedTime)
{
    if(this->_currentAction == NULL)
        return;

    if(this->_currentAction->onFrameMove(elapsedTime) == false && this->_callbackProc != NULL)
        this->_callbackProc(*this, this->_currentActionName);
}

void animation::onFrameRender(dcontextable & dc, int x, int y, bool rotateVertical)
{
    if(this->_currentAction == NULL)
        return;

    this->_currentAction->onFrameRender(dc, this->_sprite, x, y, rotateVertical);
}