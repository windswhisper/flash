#include "SocketClient.h"
bool SocketClient::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getWinSize();
	client = nullptr;//��ʼ��Ϊ��ָ��

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	addChild(menu);



	auto lblInit = Label::create("init socket", "Arial", 72);
	auto menuInit = MenuItemLabel::create(lblInit, [=](Ref *sender){
		//1.connect��������ʵ��
		client = SocketIO::connect("ws://111.206.45.12:30219", *this);
		client->setTag("init socket");
		//4.��ʼ����ʱ������һ����������ʹ��on�����¼��ͻ�ȡ���յ�������
		client->on("loginresult", [=](SIOClient *client, const std::string &data){//ʹ��C++��������ʵ��
			log("login result is :%s", data.c_str());
		});
	});
	menuInit->setPosition(size / 2);
	menu->addChild(menuInit);




	auto lblSend = Label::create("send message", "Arial", 72);
	auto menuSend = MenuItemLabel::create(lblSend, [=](Ref *sender){
		//2.send������������
		client->send("hello socket.io");
	});
	menuSend->setPosition(size.width / 2, size.height / 2 - 50);
	menu->addChild(menuSend);



	auto lblSendEvent = Label::create("emit event", "Arial", 72);
	auto menuSendEvent = MenuItemLabel::create(lblSendEvent, [=](Ref *sender){
		//3.�����������login�¼����������ֺ����봫��������  
		client->emit("login", "[{\"name\":\"myname\",\"pwd\":\"mypwd\"}]");
	});
	menuSendEvent->setPosition(size.width / 2, size.height / 2 - 100);
	menu->addChild(menuSendEvent);




	return true;
}

void SocketClient::onConnect(SIOClient* client){
	log("onConnect");
	log("%s connect", client->getTag());
}

void SocketClient::onMessage(SIOClient* client, const std::string& data){
	log("onMessage");
	log("%s received content is:%s", client->getTag(), data.c_str());
}

void SocketClient::onClose(SIOClient * client){
	log("onClose");
	log("%s is closed", client->getTag());
}
void SocketClient::onError(SIOClient* client, const std::string& data){
	log("onError");
	log("%s error is:%s", client->getTag(), data.c_str());
}