#include "Base.h"
#include "App.h"

using namespace Scene;

Scene::BaseScene::BaseScene(PB::Windows::sprite * sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName, int width, int height) : scene(sprite, width, height, backgroundSprite, backgroundName)
{
}

Scene::BaseScene::BaseScene(const std::string & filename, PB::Windows::sprite * sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName) : scene(filename, sprite, backgroundSprite, backgroundName)
{
}

Scene::BaseScene::~BaseScene()
{
}

//
// addEvent
//  이벤트 핸들러를 등록한다.
//
// Parameters
//  method              json의 메소드 이름
//  callbackRoutine     호출될 이벤트 핸들러
//
// Return
//  성공시 true, 실패시 false(현재는 항상 true)
//
bool BaseScene::addEvent(const std::string & method, BBPacketRoutine callbackRoutine)
{
    this->_eventTable.insert(std::make_pair(method, callbackRoutine));
    return true;
}

//
// onReceive
//  서버로부터 데이터를 수신했을 때 호출되는 메소드
//  등록한 이벤트 테이블과 대응되는 핸들러가 존재한다면 호출한다.
//
// Parameters
//  socket              서버 소켓
//  json                전달받은 json 객체
//
// Return
//  없음
//
void BaseScene::onReceive(App & app, Json::Value & response)
{
	if(response.isMember("method") == false)
		return;

    std::string             method      = response["method"].asString();
    Json::Value             request;

	request["method"]       = method;
    try
    {
        // 이벤트 테이블로부터 대응되는 핸들러 메소드를 찾는다.
        std::unordered_map<std::string, BBPacketRoutine>::iterator i = this->_eventTable.find(method);
        if(i == this->_eventTable.end())
            throw std::exception("Undefined 'method' field");

        
        request["success"]              = true;

        // 호출한다.
        if((this->*i->second)(app, request, response) == false)
            return;

        // 핸들러로부터 얻은 request 객체를 서버에 보낸다.
        //socket.send(encodeJson(request));
    }
    catch(std::exception& e)
    {
        request["success"]              = false;
        request["error"]                = e.what();
        //socket.send(encodeJson(request));         // 이 부분 주석 풀면 렉 엄청 걸림
    }

	
	Json::FastWriter writer;
	std::string jsons = writer.write(response);

	ostream& ostream = app.out_stream();
	ostream.write_u32(jsons.size())
		.write(jsons.data(), jsons.size());
}

void BaseScene::onDestroy()
{
    this->_sound.stop();
}