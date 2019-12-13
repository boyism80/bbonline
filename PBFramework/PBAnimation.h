#ifndef __PBANIMATION_H__
#define __PBANIMATION_H__

#include <string>
#include <vector>
#include "PBDeviceContext.h"

#include "PBSprite.h"

namespace PB { namespace Windows {

class __declspec(dllexport) animate_frame : public virtual object
{
private:
    float                   _duration;
    int                     _x, _y;
    std::string             _name;

    friend class animation;

public:
    animate_frame(const std::string& name, int x, int y, float duration);
    ~animate_frame();

public:
    float                   duration() const;
    int                     x() const;
    int                     y() const;
    const std::string&      name() const;
};




class __declspec(dllexport) animate_action : public virtual object
{
public:
    typedef std::vector<animate_frame*> frame_list;

private:
    int                     _current;
    frame_list              _animateFrames;
    bool                    _isLoop;
    float                   _elapsedTime;

    friend class animation;

public:
    animate_action(bool isLoop = false);
    ~animate_action();

private:
    void                    addFrame(animate_frame* animateFrame);
    bool                    next();

public:
    float                   duration() const;
    const animate_frame&    currentFrame() const;
    void                    reset();

public:
    bool                    onFrameMove(float elapsedTime);
    void                    onFrameRender(dcontextable& dc, sprite* sprite, int x, int y, bool rotateVertical = false);
};




class __declspec(dllexport) animation : public virtual object
{
public:
    typedef void (*animation_handler) (animation& animation, const std::string& actionName);

public:
    typedef struct std::unordered_map<std::string, animate_action*> action_map;

private:
    sprite*                 _sprite;
    action_map              _animateActions;
    animate_action*         _currentAction;
    std::string             _currentActionName;
    bool                    _isRunning;
    std::string             _defaultActionName;
    std::string             _previousActionName;
    animation_handler       _callbackProc;

public:
    animation(const std::string& filename, PB::Windows::sprite* sprite, const std::string& defaultActionName = "", animation_handler callbackProc = NULL);
    ~animation();

private:
    bool                    load(const std::string& filename);

public:
    bool                    change(const std::string& actionName);
    void                    defaultActionName(const std::string& name);
    const std::string&      defaultActionName() const;
    void                    stop();
    void                    resume();
    sprite*                 sprite() const;
    int                     currentWidth() const;
    int                     currentHeight() const;

    void                    restoreDefault();
    void                    restorePrevious();

public:
    void                    onFrameMove(float elapsedTime);
    void                    onFrameRender(dcontextable& dc, int x, int y, bool rotateVertical = false);
};

} }


#endif // !__PBANIMATION_H__
