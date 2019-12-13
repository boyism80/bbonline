#include "Base.h"

using namespace Scene;

Scene::Base::Base(PB::Windows::sprite * sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName, int width, int height) : scene(sprite, width, height, backgroundSprite, backgroundName)
{
}

Scene::Base::Base(const std::string & filename, PB::Windows::sprite * sprite, PB::Windows::sprite* backgroundSprite, const std::string& backgroundName) : scene(filename, sprite, backgroundSprite, backgroundName)
{
}

Scene::Base::~Base()
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
bool Base::addEvent(const std::string & method, BBPacketRoutine callbackRoutine)
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
void Base::onReceive(tcp & socket, Json::Value & response)
{
    std::string             method      = response["method"].asString();
    Json::Value             request;
    request["method"]                   = method;

    try
    {
        // 이벤트 테이블로부터 대응되는 핸들러 메소드를 찾는다.
        std::unordered_map<std::string, BBPacketRoutine>::iterator i = this->_eventTable.find(method);
        if(i == this->_eventTable.end())
            throw std::exception("Undefined 'method' field");

        
        request["success"]              = true;

        // 호출한다.
        if((this->*i->second)(socket, request, response) == false)
            return;

        // 핸들러로부터 얻은 request 객체를 서버에 보낸다.
        socket.send(encodeJson(request));
    }
    catch(std::exception& e)
    {
        request["success"]              = false;
        request["error"]                = e.what();
        //socket.send(encodeJson(request));         // 이 부분 주석 풀면 렉 엄청 걸림
    }
}

void Base::onDestroy()
{
    this->_sound.stop();
}

std::vector<char> Base::encodeJson(const Json::Value & json)
{
    
    std::string         str = json.toStyledString();
    int                 size = str.length();
    char*               sizeRef = (char*)&size;

    std::vector<char>   buffer;
    buffer.insert(buffer.end(), sizeRef, sizeRef + sizeof(int));
    buffer.insert(buffer.end(), str.begin(), str.end());
    return buffer;
}

bool Base::decodeJson(const std::vector<char>& bytes, Json::Value& json)
{
    std::string     str(bytes.begin(), bytes.end());
    Json::Reader    reader;

    if (reader.parse(str, json) == false)
        return false;

    return true;
}