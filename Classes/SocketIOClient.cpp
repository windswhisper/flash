#include "SocketIOClient.h"

SocketIOClient::SocketIOClient()
{
}
SocketIOClient::~SocketIOClient()
{
}

SocketIOClient* SocketIOClient::getInstance()
{
    if(_socketIOClient==NULL)
    {
        _socketIOClient = new SocketIOClient();
    }
    return _socketIOClient;
}

void SocketIOClient::connect()
{
    client = SocketIO::connect("ws://111.206.45.12:30219", *this);
    client->setTag("init socket");
    //4.初始化的时候设置一个监听器：使用on监听事件和获取接收到的数据
    client->on("loginresult",[=](SIOClient *client,const std::string &data){//使用C++匿名函数实现
        log("login result is :%s",data.c_str());
    });
}

void SocketIOClient::send(char *msg)
{
    client->send(msg);
}

void SocketIOClient::onConnect(SIOClient* client){
    log("onConnect");
    log("%s connect",client->getTag());
}

void SocketIOClient::onMessage(SIOClient* client, const std::string& data){
    log("onMessage");
    log("%s received content is:%s",client->getTag(),data.c_str());
}

void SocketIOClient::onClose(SIOClient * client){
    log("onClose");
    log("%s is closed",client->getTag());
}
void SocketIOClient::onError(SIOClient* client, const std::string& data){
    log("onError");
    log("%s error is:%s",client->getTag(),data.c_str());
}
