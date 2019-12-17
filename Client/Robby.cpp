#include "Robby.h"
#include "App.h"

using namespace Scene;

Scene::Robby::Robby(const std::string& filename, PB::Windows::sprite * sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName) : BaseScene(filename, sprite, backgroundSprite, backgroundName), 
    _characterSprite(L"Resources/sprite/character.pbs"), _rooms(Json::arrayValue)
{
    this->_x            = 100;
    this->_y            = 300;
}

Robby::~Robby()
{}

window * Scene::Robby::createRoomWindow(const Json::Value & createdRoom)
{
    char            windowName[256];
    sprintf(windowName, "room window %d", createdRoom["id"].asInt());
    
    window*         createdWindow = this->get(windowName);
    if(createdWindow == NULL)
        createdWindow = new PB::Windows::Control::window("Resources/windows/RoomInfo.pbw", this->sprite(), (PB::Windows::Control::window*)this, windowName);

    createdWindow->get("contents")->get("id")->text(std::to_string(createdRoom["id"].asInt()));
    createdWindow->get("contents")->get("name")->text(createdRoom["name"].asString());
    createdWindow->get("contents")->get("client count")->text(std::to_string(createdRoom["client count"].asInt()));
    createdWindow->get("contents")->get("capacity")->text(std::to_string(createdRoom["capacity"].asInt()));
    createdWindow->get("contents")->get("state")->text(createdRoom["state"].asInt() == 0 ? "IDLE" : "PLAYING");

    return createdWindow;
}

bool Scene::Robby::deleteRoomWindow(int id)
{
    char            windowName[256];
    sprintf(windowName, "room window %d", id);
    return this->remove(windowName);
}

void Robby::onCreate()
{
    __super::onCreate();
    App::instance()->scale(1.0f);

    this->addEvent("room list",     static_cast<BaseScene::BBPacketRoutine>(&Robby::roomListRoutine));
    this->addEvent("create room",   static_cast<BaseScene::BBPacketRoutine>(&Robby::createRoomRoutine));
    this->addEvent("leave room",    static_cast<BaseScene::BBPacketRoutine>(&Robby::leaveRoomRoutine));
    this->addEvent("enter room",    static_cast<BaseScene::BBPacketRoutine>(&Robby::enterRoomRoutine));

	Json::Value         json;
	json["method"]      = "room list";

    App*                app = (App*)App::instance();
    app->send(json);
}

void Robby::onFrameMove(float elapsedTime)
{
    __super::onFrameMove(elapsedTime);

    char            windowName[256];
    int             index = 0;
    int             maximum = 4;
csection::enter("rooms");
    for (auto i = this->_rooms.begin(); i != this->_rooms.end(); i++)
    {
        Json::Value& room = *i;
        sprintf(windowName, "room window %d", room["id"].asInt());

        window* window = (*this)[windowName];
        if(window == NULL)
            break;

        int         row = (index / 2);
        int         col = (index % 2);
        window->position(col * window->width(), row * window->height());
        index++;

        if(index > maximum - 1)
            break;
    }
csection::leave("rooms");
}

void Robby::onFrameRender(dcontextable& dc, float elapsedTime)
{
    __super::onFrameRender(dc, elapsedTime);
}

void Scene::Robby::onCommand(window * control, const std::string & action, Json::Value & parameters)
{
    App*                app = (App*)App::instance();
    window*             dialog = (*this)["create room dialog"];

    try
    {
        // 다이얼로그 하위 컨트롤 이벤트
        if (control->parent() == dialog)
        {
            if (control->id().compare("OK") == 0)
            {
                window* nameTextBox = (*dialog)["name"];
                window* capacityTextBox = (*dialog)["capacity"];

                Json::Value         json;
                json["method"] = "create room";
                json["name"] = nameTextBox->text();
                json["capacity"] = std::stoi(capacityTextBox->text());
                app->send(json);

                dialog->visible(false);
            }
            else if (control->id().compare("cancel") == 0)
            {
                dialog->visible(false);
            }
            return;
        }

        // 동적 컨트롤 이벤트
        if(control->id().compare("contents") == 0)
        {
            const window* parent = control->parent();
            char buffer[256];
            int id = 0;
            sscanf(parent->id().c_str(), "room window %d", &id);

            Json::Value         json;
            json["method"] = "enter room";
            json["id"] = id;
            app->send(json);
        }

        // 일반 컨트롤 이벤트
        if (control->id().compare("create room") == 0)
        {
            if (action.compare("click") == 0)
            {
                (*dialog)["name"]->text("");
                (*dialog)["capacity"]->text("");
                dialog->visible(true);
                this->foreground(dialog);
            }
            
            return;
        }
    }
    catch(std::invalid_argument& e)
    {
        ::MessageBox(app->hwnd(), "Check your input value : capacity", "error", MB_OK);
    }
    catch(std::exception& e)
    {
        puts(e.what());
    }
    
}

bool Robby::onKeyboard(char vk, bool isDown)
{
    if(__super::onKeyboard(vk, isDown) == true)
        return true;

    return true;
}

void Robby::onReceive(App & app, Json::Value & root)
{
    __super::onReceive(app, root);
}

void Scene::Robby::onDestroy()
{
    __super::onDestroy();
csection::enter("rooms");
    for(auto i = this->_rooms.begin(); i != this->_rooms.end(); i++)
    {
        Json::Value room = *i;
        this->deleteRoomWindow(room["id"].asInt());
    }
csection::leave("rooms");
}

bool Robby::roomListRoutine(tcp & socket, Json::Value& request, const Json::Value& response)
{
csection::enter("rooms");
    this->_rooms.clear();
    this->_rooms = response["rooms"];

    for(auto i = this->_rooms.begin(); i != this->_rooms.end(); i++)
        this->add(this->createRoomWindow(*i));
csection::leave("rooms");

    return false;
}

bool Robby::createRoomRoutine(tcp & socket, Json::Value& request, const Json::Value& response)
{
    App*                app = (App*)App::instance();

    if (response["success"].asBool() == false)
    {
        ::MessageBox(app->hwnd(), response["error"].asCString(), "error", MB_OK);
        return false;
    }

    if(response["mine"].asBool())
    {
        app->trans("stand by");
        return false;
    }

csection::enter("rooms");
    this->_rooms = response["rooms"];
    
    this->add(this->createRoomWindow(response["created room"]));
csection::leave("rooms");

    return false;
}

bool Robby::enterRoomRoutine(tcp & socket, Json::Value& request, const Json::Value& response)
{
    App*                app = (App*)App::instance();

    if (response["success"].asBool() == false)
    {
        ::MessageBox(app->hwnd(), response["error"].asCString(), "error", MB_OK);
        return false;
    }
    
    app->trans("stand by");
    return false;
}

bool Scene::Robby::leaveRoomRoutine(tcp &, Json::Value& request, const Json::Value& response)
{
    App*                app = (App*)App::instance();
    if (response["success"].asBool() == false)
    {
        ::MessageBox(app->hwnd(), response["error"].asCString(), "error", MB_OK);
        return false;
    }

csection::enter("rooms");
    this->_rooms = response["rooms"];

    this->deleteRoomWindow(response["deleted room"].asInt());
csection::leave("rooms");
    return false;
}
