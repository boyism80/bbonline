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
//  �̺�Ʈ �ڵ鷯�� ����Ѵ�.
//
// Parameters
//  method              json�� �޼ҵ� �̸�
//  callbackRoutine     ȣ��� �̺�Ʈ �ڵ鷯
//
// Return
//  ������ true, ���н� false(����� �׻� true)
//
bool BaseScene::addEvent(const std::string & method, BBPacketRoutine callbackRoutine)
{
    this->_eventTable.insert(std::make_pair(method, callbackRoutine));
    return true;
}

//
// onReceive
//  �����κ��� �����͸� �������� �� ȣ��Ǵ� �޼ҵ�
//  ����� �̺�Ʈ ���̺�� �����Ǵ� �ڵ鷯�� �����Ѵٸ� ȣ���Ѵ�.
//
// Parameters
//  socket              ���� ����
//  json                ���޹��� json ��ü
//
// Return
//  ����
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
        // �̺�Ʈ ���̺�κ��� �����Ǵ� �ڵ鷯 �޼ҵ带 ã�´�.
        std::unordered_map<std::string, BBPacketRoutine>::iterator i = this->_eventTable.find(method);
        if(i == this->_eventTable.end())
            throw std::exception("Undefined 'method' field");

        
        request["success"]              = true;

        // ȣ���Ѵ�.
        if((this->*i->second)(app, request, response) == false)
            return;

        // �ڵ鷯�κ��� ���� request ��ü�� ������ ������.
        //socket.send(encodeJson(request));
    }
    catch(std::exception& e)
    {
        request["success"]              = false;
        request["error"]                = e.what();
        //socket.send(encodeJson(request));         // �� �κ� �ּ� Ǯ�� �� ��û �ɸ�
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