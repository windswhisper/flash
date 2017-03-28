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
	client = nullptr;//初始化为空指针

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	addChild(menu);



	auto lblInit = Label::create("init socket", "Arial", 72);
	auto menuInit = MenuItemLabel::create(lblInit, [=](Ref *sender){
		//1.connect方法创建实例
		client = SocketIO::connect("ws://111.206.45.12:30219", *this);
		client->setTag("init socket");
		//4.初始化的时候设置一个监听器：使用on监听事件和获取接收到的数据
		client->on("loginresult", [=](SIOClient *client, const std::string &data){//使用C++匿名函数实现
			log("login result is :%s", data.c_str());
		});
	});
	menuInit->setPosition(size / 2);
	menu->addChild(menuInit);




	auto lblSend = Label::create("send message", "Arial", 72);
	auto menuSend = MenuItemLabel::create(lblSend, [=](Ref *sender){
		//2.send方法发送数据
		client->send("hello socket.io");
	});
	menuSend->setPosition(size.width / 2, size.height / 2 - 50);
	menu->addChild(menuSend);



	auto lblSendEvent = Label::create("emit event", "Arial", 72);
	auto menuSendEvent = MenuItemLabel::create(lblSendEvent, [=](Ref *sender){
		//3.向服务器发送login事件，并把名字和密码传给服务器  
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