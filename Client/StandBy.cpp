#include "StandBy.h"
#include "App.h"

using namespace Scene;

StandBy::StandBy(const std::string& filename, PB::Windows::sprite* sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName) : BaseScene(filename, sprite, backgroundSprite, backgroundName), 
    _userList(Json::arrayValue)
{
    for(int i = 0; i < MAX_CAPACITY; i++)
    {
        std::string windowName = std::string("client ").append(std::to_string(i));
        window* createdWindow = new window("Resources/windows/ready state.pbw", this->sprite(), this, windowName.c_str());

        int row = i / (MAX_CAPACITY / 2);
        int col = i % (MAX_CAPACITY / 2);
        createdWindow->position(col * createdWindow->width(), row * createdWindow->height());
        this->add(createdWindow);
    }
}

StandBy::~StandBy()
{}

void Scene::StandBy::updateReadyStateWindow()
{
    for(int i = 0; i < MAX_CAPACITY; i++)
    {
        std::string windowName = std::string("client ").append(std::to_string(i));
        this->get(windowName)->get("contents")->get("client")->text("");
        this->get(windowName)->get("contents")->get("state")->text("");
    }

    for(auto i = this->_userList.begin(); i != this->_userList.end(); i++)
    {
        Json::Value user = *i;
        std::string windowName = std::string("client ").append(std::to_string(user["order"].asInt()));

        const std::string& id = std::to_string(user["id"].asInt());
        const std::string state = user["ready"].asBool() ? "READY" : "IDLE";

        this->get(windowName)->get("contents")->get("client")->text(id);
        this->get(windowName)->get("contents")->get("state")->text(user["priest"].asBool() ? "PRIEST" : state);
    }
}

void StandBy::onCreate()
{
    __super::onCreate();
    App::instance()->scale(1.0f);

    this->addEvent("stand by", static_cast<BaseScene::BBPacketRoutine>(&StandBy::standByStateRoutine));
    this->addEvent("ready", static_cast<BaseScene::BBPacketRoutine>(&StandBy::readyRoutine));
    this->addEvent("leave room", static_cast<BaseScene::BBPacketRoutine>(&StandBy::disconnectedRoutine));
    this->addEvent("disconnected", static_cast<BaseScene::BBPacketRoutine>(&StandBy::disconnectedRoutine));

    App*                app = (App*)App::instance();

    Json::Value         json;
    json["method"]      = "stand by";
    app->send(json);
}

void StandBy::onFrameMove(float elapsedTime)
{
    __super::onFrameMove(elapsedTime);
}

void StandBy::onFrameRender(dcontextable& dc, float elapsedTime)
{
    __super::onFrameRender(dc, elapsedTime);
}

void Scene::StandBy::onCommand(window * control, const std::string & action, Json::Value & parameters)
{
    App*                app = (App*)App::instance();
    Json::Value         json;

    if (control->id().compare("back") == 0)
    {
        json["method"] = "leave room";
        app->send(json);
    }
    else if(control->id().compare("ready") == 0)
    {
        json["method"] = "ready";
        app->send(json);
    }
}

bool StandBy::onKeyboard(char vk, bool isDown)
{
    if (isDown == false)
        return true;

    return true;
}

void StandBy::onReceive(App & app, Json::Value & root)
{
    __super::onReceive(app, root);
}

bool StandBy::standByStateRoutine(tcp & socket, Json::Value& request, const Json::Value& response)
{
csection::enter("users");
    this->_userList = response["users"];
    this->updateReadyStateWindow();
csection::leave("users");
    
    return false;
}

bool StandBy::readyRoutine(tcp & socket, Json::Value& request, const Json::Value& response)
{
    App*                app = (App*)App::instance();

    if(response["success"].asBool() == false)
    {
        ::MessageBox(app->hwnd(), response["error"].asCString(), "error", MB_OK);
        return false;
    }

    if (response["state"] == "in game")
    {
        app->trans("game");
        return false;
    }

csection::enter("users");
    this->_userList = response["users"];
    this->updateReadyStateWindow();
csection::leave("users");


    return false;
}

bool Scene::StandBy::leaveRoomRoutine(tcp & socket, Json::Value& request, const Json::Value& response)
{
    if(response["success"].asBool() == false)
    {
        return false;
    }

    if(response["mine"].asBool())
    {
        App*                app = (App*)App::instance();
        app->trans("robby");
    }
    return false;
}

bool StandBy::disconnectedRoutine(tcp & socket, Json::Value& request, const Json::Value& response)
{
    App*                app = (App*)App::instance();

    if(response["method"].asString() == "leave room" && response["mine"].asBool())
    {
        App*                app = (App*)App::instance();
        app->trans("robby");
        return false;
    }

csection::enter("users");
    this->_userList = response["users"];
    this->updateReadyStateWindow();
csection::leave("users");
    return false;
}