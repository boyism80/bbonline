#include "PBWindow.h"

#pragma region PBWindow
PB::Windows::Control::window::window(window* parent, const std::string& id, const std::string& text, int x, int y, int width, int height, const PB::Windows::sprite * sprite, const char * spriteName, const char* hoverSpriteName, int backgroundColor) : 
    _isDown(false),
    _parent(parent),
    _id(id), 
    _initialText(text),
    _text(text), 
    _area(x, y, width, height), 
    _sprite(sprite), 
    _spriteName(NULL),
    _hoverSpriteName(NULL),
    _foregroundWindow(NULL),
    _isHover(false),
    _visible(true),
    _backgroundColor(backgroundColor)
{
    this->_zindex = 0;

    if(spriteName != NULL)
    {
        this->_spriteName = new char[strlen(spriteName) + 1];
        strcpy(this->_spriteName, spriteName);
    }

    if (hoverSpriteName != NULL)
    {
        this->_hoverSpriteName = new char[strlen(hoverSpriteName) + 1];
        strcpy(this->_hoverSpriteName, hoverSpriteName);
    }
}

PB::Windows::Control::window::window(const std::string & filename, const PB::Windows::sprite * sprite, window* parent, const char* id, int backgroundColor) :
    _isDown(false),
    _spriteName(NULL),
    _hoverSpriteName(NULL),
    _foregroundWindow(NULL),
    _isHover(false),
    _visible(true),
    _backgroundColor(backgroundColor)
{
    std::ifstream file(filename, std::ios::binary);
    if(file.is_open() == false)
        throw std::exception("Cannot find file.");

    int numChildren = 0;
    window* createdRoot = window::load(file, sprite, NULL, &numChildren, parent);
    this->copy(createdRoot);
    
    this->_parent = parent;

    if(id != NULL)
        this->_id = id;

    for(int i = 0; i < numChildren; i++)
        this->add(window::load(file, sprite, this));

    delete createdRoot;
    file.close();
}

PB::Windows::Control::window::window(const window* window, PB::Windows::Control::window * parent) : 
    _isDown(false),
    _spriteName(NULL),
    _hoverSpriteName(NULL),
    _foregroundWindow(NULL),
    _isHover(false),
    _visible(true)
{
    this->copy(window, parent);
}

PB::Windows::Control::window::~window()
{
    for(auto i = this->_windows.begin(); i != this->_windows.end(); i++)
    {
        if(*i == NULL)
            continue;

        delete *i;
    }
    this->_windows.clear();

    if(this->_spriteName != NULL)
        delete[] this->_spriteName;

    if(this->_hoverSpriteName != NULL)
        delete[] this->_hoverSpriteName;
}

void PB::Windows::Control::window::hover(bool value)
{
    if(this->_isHover != value)
        this->onHoverStateChanged(value);
    this->_isHover = value;
}

int PB::Windows::Control::window::x() const
{
    return this->_area.left;
}

int PB::Windows::Control::window::y() const
{
    return this->_area.top;
}

int PB::Windows::Control::window::width() const
{
    return this->_area.width();
}

int PB::Windows::Control::window::height() const
{
    return this->_area.height();
}

const PB::Windows::Control::window * PB::Windows::Control::window::parent() const
{
    return this->_parent;
}

const PB::Windows::rect& PB::Windows::Control::window::area() const
{
    return this->_area;
}

void PB::Windows::Control::window::area(int x, int y, int width, int height)
{
    this->_area.position(x, y);
    this->_area.resize(width, height);
}

void PB::Windows::Control::window::position(int x, int y)
{
    this->_area.position(x, y);
}

const PB::Windows::sprite * PB::Windows::Control::window::sprite() const
{
    return this->_sprite;
}

const char* PB::Windows::Control::window::spriteName() const
{
    return this->_spriteName;
}

PB::Windows::rect PB::Windows::Control::window::absoluteArea() const
{
    if(this->_parent != NULL)
    {
        auto adjusted = this->_area;
        adjusted.move(this->_parent->x(), this->_parent->y());
        return adjusted;
    }

    return this->_area;
}

const std::string & PB::Windows::Control::window::id() const
{
    return this->_id;
}

const std::string & PB::Windows::Control::window::text() const
{
    return this->_text;
}

void PB::Windows::Control::window::text(const std::string & text)
{
    this->_text = text;
}

int PB::Windows::Control::window::backgroundColor() const
{
    return this->_backgroundColor;
}

PB::Windows::Control::window * PB::Windows::Control::window::add(window * window)
{
    if(this->get(window->id()) != NULL)
        return NULL;

csection::enter("windows");
    this->_windows.push_back(window);
    std::sort(this->_windows.begin(), this->_windows.end(), [](const PB::Windows::Control::window* left, const PB::Windows::Control::window* right) -> bool
    {
        return left->_zindex < right->_zindex;
    });

    this->gotoTop(window);
csection::leave("windows");

    return window;
}

bool PB::Windows::Control::window::remove(const std::string & id)
{
    window* existed = this->get(id);
    if(existed == NULL)
        return false;

csection::enter("windows");
    auto i = std::find(this->_windows.begin(), this->_windows.end(), existed);
csection::leave("windows");
    if(i == this->_windows.end())
        return false;

csection::enter("windows");
    delete *i;
    this->_windows.erase(i);
csection::leave("windows");
    return true;
}

PB::Windows::Control::window * PB::Windows::Control::window::get(const std::string & id)
{
    window* window = NULL;
csection::enter("windows");
    for (auto i = this->_windows.begin(); i != this->_windows.end(); i++)
    {
        if (*i == NULL)
            continue;

        if ((*i)->id().compare(id) != 0)
            continue;

        window = *i;
        break;
    }
csection::leave("windows");

    return window;
}

PB::Windows::Control::window * PB::Windows::Control::window::foreground() const
{
    return this->_foregroundWindow;
}

bool PB::Windows::Control::window::foreground(window * window)
{
    if(window == NULL)
    {
        this->_foregroundWindow = NULL;
        return true;
    }

csection::enter("windows");
    auto i = std::find(this->_windows.begin(), this->_windows.end(), window);
csection::leave("windows");
    if(i == this->_windows.end())
        return false;

    this->_foregroundWindow = *i;
    this->gotoTop((*i));
    return true;
}

PB::Windows::Control::window* PB::Windows::Control::window::copy(const PB::Windows::Control::window * window, PB::Windows::Control::window* parent)
{
    this->_parent = parent;
    this->_id = window->_id;
    this->_initialText = window->_text;
    this->_text = window->_text;
    this->_area = window->_area;
    this->_sprite = window->_sprite;
    this->_visible = window->_visible;
    this->_backgroundColor = window->_backgroundColor;

    if (this->_spriteName != NULL)
        delete[] this->_spriteName;
    this->_spriteName = NULL;

    if (window->_spriteName != NULL)
    {
        this->_spriteName = new char[strlen(window->_spriteName) + 1];
        strcpy(this->_spriteName, window->_spriteName);
    }

    if (this->_hoverSpriteName != NULL)
        delete[] this->_hoverSpriteName;
    this->_hoverSpriteName = NULL;

    if (window->_hoverSpriteName != NULL)
    {
        this->_hoverSpriteName = new char[strlen(window->_hoverSpriteName) + 1];
        strcpy(this->_hoverSpriteName, window->_hoverSpriteName);
    }

    return this;
}

PB::Windows::Control::window * PB::Windows::Control::window::clone(window * parent)
{
    return new window(this, parent);
}

bool PB::Windows::Control::window::visible() const
{
    return this->_visible;
}

void PB::Windows::Control::window::visible(bool value)
{
    this->_visible = value;
}

PB::Windows::Control::window * PB::Windows::Control::window::gotoTop(window * window)
{
csection::enter("windows");
    if (this->_windows.empty() == false)
    {
        PB::Windows::Control::window* last = this->_windows.back();
        window->_zindex = last->_zindex + 1;
    }

    std::sort(this->_windows.begin(), this->_windows.end(), [](const PB::Windows::Control::window* left, const PB::Windows::Control::window* right) -> bool
    {
        return left->_zindex < right->_zindex;
    });

    int index = 0;
    for(auto i = this->_windows.begin(); i != this->_windows.end(); i++)
        (*i)->_zindex = index++;
csection::leave("windows");

    return window;
}

bool PB::Windows::Control::window::hover() const
{
    return this->_isHover;
}

PB::Windows::Control::window * PB::Windows::Control::window::operator[](const std::string & id)
{
    return this->get(id);
}

PB::Windows::Control::window& PB::Windows::Control::window::operator=(const window & window)
{
    return *this->copy(&window);
}

PB::Windows::Control::window::operator const PB::Windows::sprite*() const
{
    return this->_sprite;
}

void PB::Windows::Control::window::onCreate()
{
    this->_text = this->_initialText;
csection::enter("windows");
    for (auto i = this->_windows.begin(); i != this->_windows.end(); i++)
    {
        if (*i != NULL)
            (*i)->onCreate();
    }
csection::leave("windows");
}

void PB::Windows::Control::window::onFrameMove(float elapsedTime)
{
csection::enter("windows");
    for (auto i = this->_windows.begin(); i != this->_windows.end(); i++)
    {
        if (*i != NULL)
            (*i)->onFrameMove(elapsedTime);
    }
csection::leave("windows");
}

void PB::Windows::Control::window::onFrameRender(dcontextable & dc, float elapsedTime)
{
    if(this->_visible == false)
        return;

    rect canvas(0, 0, this->width(), this->height());

    try
    {
        if(this->_sprite == NULL)
            throw NULL;

        const char* spriteName = NULL;

        if(this->_isHover)
        {
            if (this->_hoverSpriteName == NULL)
                spriteName = this->_spriteName;
            else
                spriteName = this->_hoverSpriteName;
        }
        else
        {
            spriteName = this->_spriteName;
        }

        spriteName = this->_isHover ? this->_hoverSpriteName : this->_spriteName;
        if(spriteName == NULL && this->_isHover)
            spriteName = this->_spriteName;

        if(spriteName == NULL)
            throw NULL;
        
        dc.draw(this->_sprite->get(spriteName), canvas);
    }
    catch(...)
    {
        dc.fillRect(canvas, this->_backgroundColor);
        //dc.drawRect(canvas);
    }
}

void PB::Windows::Control::window::onGUIRender(dcontextable & dc, float elapsedTime)
{
    if(this->_visible == false)
        return;

csection::enter("windows");
    for (auto i = this->_windows.begin(); i != this->_windows.end(); i++)
    {
        window* window = *i;
        if(window == NULL)
            continue;

        dc_buffer stream(dc, window->_area, window->backgroundColor());
        window->onFrameRender(stream, elapsedTime);
        window->onGUIRender(stream, elapsedTime);
        
        dc.update(stream);
    }
csection::leave("windows");
}

void PB::Windows::Control::window::onCommand(window * control, const std::string & action, Json::Value & parameters)
{
    if(this->_parent != NULL)
        this->_parent->onCommand(control, action, parameters);
}

void PB::Windows::Control::window::onDestroy()
{
csection::enter("windows");
    for (auto i = this->_windows.begin(); i != this->_windows.end(); i++)
    {
        if (*i != NULL)
            (*i)->onDestroy();
    }
csection::leave("windows");
}

void PB::Windows::Control::window::onHoverStateChanged(bool isHover)
{
    this->_isDown = false;
}

// 키보드 이벤트를 더 이상 진행시키고 싶지 않으면
// true를 리턴하고
// 이벤트를 계속 진행하고 싶다면
// false를 리턴
bool PB::Windows::Control::window::onKeyboard(char vk, bool isDown)
{
    if(this->_foregroundWindow == NULL)
        return false;

    return this->_foregroundWindow->onKeyboard(vk, isDown);
}

bool PB::Windows::Control::window::onCharacter(wchar_t key, bool isDown)
{
    if (this->_foregroundWindow == NULL)
        return false;

    return this->_foregroundWindow->onCharacter(key, isDown);
}

bool PB::Windows::Control::window::onMouse(const point& location, bool isLButtonDown, bool isRButtonDown, bool isLButtonUp, bool isRButtonUp, bool isMove)
{
    window* window = NULL;
    bool bubbleChain = true;

csection::enter("windows");
    for (auto i = this->_windows.begin(); i != this->_windows.end(); i++)
    {
        if (*i == NULL)
            continue;

        if((*i)->visible() == false)
            continue;

        auto wndRect = (*i)->absoluteArea();
        if(wndRect.contains(location) == false)
        {
            (*i)->hover(false);
            continue;
        }

        if(bubbleChain)
        {
            (*i)->hover(true);
            window = *i;
            if (window->onMouse(location, isLButtonDown, isRButtonDown, isLButtonUp, isRButtonUp, isMove) == true)
                bubbleChain = false;
        }
    }

    if(window != NULL && isLButtonDown)
        this->foreground(window);

    try
    {
        if(bubbleChain == false)
            throw NULL;

        if (isLButtonDown)
        {
            this->_isDown = true;
            throw NULL;
        }
        
        if (isLButtonUp && this->_isDown)
        {
            Json::Value parameters;
            parameters["location"] = Json::Value();
            parameters["location"]["x"] = location.x;
            parameters["location"]["y"] = location.y;
            this->onCommand(this, "click", parameters);

            this->_isDown = false;
            throw NULL;
        }
    }
    catch(...)
    { }

csection::leave("windows");
    return true;
}

PB::Windows::Control::window* PB::Windows::Control::window::load(std::ifstream & file, const PB::Windows::sprite * sprite, std::string* purpose, int* numChildren, window* parent)
{
    char                isize = 0;
    file.read(&isize, sizeof(char));

    char*               id = new char[isize + 1];
    file.read(id, isize);
    id[isize] = 0;


    char                ssize = 0;
    file.read(&ssize, sizeof(char));

    char*               spriteName = NULL;
    if (ssize > 0)
    {
        spriteName = new char[ssize + 1];
        file.read(spriteName, ssize);
        spriteName[ssize] = 0;
    }

    int                 x, y;
    file.read((char*)&x, sizeof(int));
    file.read((char*)&y, sizeof(int));

    int                 width, height;
    file.read((char*)&width, sizeof(int));
    file.read((char*)&height, sizeof(int));

    char                psize = 0;
    file.read(&psize, sizeof(char));

    char*               cpurpose = new char[psize + 1];
    file.read(cpurpose, psize);
    cpurpose[psize] = 0;
    if(purpose != NULL)
        *purpose = cpurpose;

    char                tsize = 0;
    file.read(&tsize, sizeof(char));

    char*               text = new char[tsize + 1];
    file.read(text, tsize);
    text[tsize] = 0;

    bool                visible = false;
    file.read((char*)&visible, sizeof(bool));

    int                 csize = 0;
    file.read((char*)&csize, sizeof(int));
    if(numChildren != NULL)
        *numChildren = csize;

    window*             createdWindow = new window(parent, id, text, x, y, width, height, sprite, spriteName);
    createdWindow->visible(visible);

    delete[] id;
    delete[] cpurpose;
    delete[] text;
    if (spriteName != NULL)
        delete[] spriteName;

    return createdWindow;
}

PB::Windows::Control::window* PB::Windows::Control::window::load(std::ifstream & file, const PB::Windows::sprite* sprite, window * parent)
{
    std::string         purpose;
    int                 csize = 0;
    window*             source = window::load(file, sprite, &purpose, &csize);
    window*             created = NULL;
    if(purpose.compare("Button") == 0)
        created = (window*)new button(source, parent);
    else if (purpose.compare("EditText") == 0)
        created = (window*)new textbox(source, parent);
    else if(purpose.compare("Label") == 0)
        created = (window*)new label(source, parent);
    else
        created = new window(source, parent);

    if(purpose.compare("Dialog") == 0)
        created->visible(false);

    for(int i = 0; i < csize; i++)
        created->add(window::load(file, sprite, created));

    delete source;
    return created;
}

#pragma endregion


#pragma region PBButton
PB::Windows::Control::button::button(window * parent, const std::string & id, const std::string & text, int x, int y, int width, int height, const PB::Windows::sprite * sprite, const char * spriteName) :
    window(parent, id, text, x, y, width, height, sprite, spriteName)
{
}

PB::Windows::Control::button::button(const window* button, window* parent) : button(parent, button->id(), button->text(), button->x(), button->y(), button->width(), button->height(), button->sprite(), button->spriteName())
{
}

PB::Windows::Control::button::~button()
{
}

PB::Windows::Control::window * PB::Windows::Control::button::clone(window* parent)
{
    return new button(this, parent);
}

void PB::Windows::Control::button::onFrameMove(float elapsedTime)
{

}

void PB::Windows::Control::button::onFrameRender(dcontextable & dc, float elapsedTime)
{
    if(this->_spriteName != NULL)
    {
        __super::onFrameRender(dc, elapsedTime);
    }
    else
    {
        const std::string& text = this->text();
        SIZE size;
        GetTextExtentPoint(dc, text.c_str(), text.length(), &size);

        rect canvas(0, 0, this->width(), this->height());
        point drawTextLocation(canvas.left + (canvas.width() - size.cx) / 2.0f, canvas.top + (canvas.height() - size.cy) / 2.0f);
        int backgroundColor = RGB(33, 150, 243);
        if (this->hover())
            backgroundColor = RGB(255, 165, 0);

        dc.fillRect(canvas, backgroundColor);
        dc.drawText(drawTextLocation.x, drawTextLocation.y, text, RGB(255, 255, 255));
    }
}

void PB::Windows::Control::button::onCommand(window * control, const std::string & action, Json::Value & parameters)
{
    __super::onCommand(control, action, parameters);
}

void PB::Windows::Control::button::onHoverStateChanged(bool isHover)
{
}

#pragma endregion


#pragma region PBTextBox
PB::Windows::Control::textbox::textbox(window * parent, const std::string & id, const std::string & text, int x, int y, int width, int height, const PB::Windows::sprite * sprite, const char * spriteName) :
    window(parent, id, text, x, y, width, height, sprite, spriteName)
{
}

PB::Windows::Control::textbox::textbox(const window* textbox, window * parent) : textbox(parent, textbox->id(), textbox->text(), textbox->x(), textbox->y(), textbox->width(), textbox->height(), textbox->sprite(), textbox->spriteName())
{
}

PB::Windows::Control::textbox::~textbox()
{
}

PB::Windows::Control::window * PB::Windows::Control::textbox::clone(window * parent)
{
    return new textbox(this, parent);
}

void PB::Windows::Control::textbox::onFrameRender(dcontextable & dc, float elapsedTime)
{
    if(this->_spriteName != NULL)
    {
        __super::onFrameRender(dc, elapsedTime);
    }
    else
    {
        const std::string& text = this->text();
        SIZE size;
        GetTextExtentPoint(dc, text.c_str(), text.length(), &size);

        rect canvas(0, 0, this->width(), this->height());
        point drawTextLocation(canvas.left + (canvas.width() - size.cx) / 2.0f, canvas.top + (canvas.height() - size.cy) / 2.0f);
        int backgroundColor = RGB(33, 150, 243);
        if (this->hover())
            backgroundColor = RGB(255, 165, 0);

        dc.fillRect(canvas, backgroundColor);
        dc.drawText(canvas.left, drawTextLocation.y, text, RGB(255, 255, 255));
    }
}

bool PB::Windows::Control::textbox::onKeyboard(char vk, bool isDown)
{
    if (isDown == false)
        return true;

    return true;
}

bool PB::Windows::Control::textbox::onCharacter(wchar_t key, bool isDown)
{
    Json::Value parameters;
    if (key == VK_BACK)
    {
        const std::string&      prev = this->text();
        if (prev.length() == 0)
            return true;

        unsigned char           last = prev.back();
        bool                    alnum = isalnum(last);
        std::string             next = prev.substr(0, max(0, prev.size() - (alnum ? sizeof(char) : sizeof(wchar_t))));
        this->text(next);

        parameters["text"] = next;
        parameters["back"] = true;
        this->onCommand(this, "text changed", parameters);
    }
    else
    {
        char stream[3] = { 0, };
        wcstombs(stream, &key, sizeof(stream));

        this->text(this->text() + stream);

        parameters["text"] = this->text();
        parameters["back"] = false;
        this->onCommand(this, "text changed", parameters);
    }

    return true;
}
#pragma endregion



#pragma region PBLabel
PB::Windows::Control::label::label(window * parent, const std::string & id, const std::string & text, int x, int y, int width, int height) : 
    window(parent, id, text, x, y, width, height)
{
}

PB::Windows::Control::label::label(const window * label, window * parent) : 
    window(label, parent)
{
}

PB::Windows::Control::label::~label()
{
}

PB::Windows::Control::window * PB::Windows::Control::label::clone(window * parent)
{
    return new label(this, parent);
}

void PB::Windows::Control::label::onFrameRender(dcontextable & dc, float elapsedTime)
{
    const std::string& text = this->text();
    SIZE size;
    GetTextExtentPoint(dc, text.c_str(), text.length(), &size);

    rect canvas(0, 0, this->width(), this->height());
    point drawTextLocation(canvas.left, canvas.top + (canvas.height() - size.cy) / 2.0f);
    dc.drawText(drawTextLocation.x, drawTextLocation.y, text, RGB(0, 0, 0));
}

bool PB::Windows::Control::label::onKeyboard(char vk, bool isDown)
{
    return false;
}

bool PB::Windows::Control::label::onMouse(const point & location, bool isLButtonDown, bool isRButtonDown, bool isLButtonUp, bool isRButtonUp, bool isMove)
{
    return false;
}
#pragma endregion