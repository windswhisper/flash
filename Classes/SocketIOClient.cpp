#include "SocketIOClient.h"

static const char* SOCKETIO_IP = "ws://111.206.45.12:30219";
//static const char* SOCKETIO_IP = "ws://127.0.0.1:8808";

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
    client = SocketIO::connect(SOCKETIO_IP, *this);
    client->setTag("n1");
}

void SocketIOClient::listen(char* event,std::function<void(SIOClient*,std::string)> callback)
{
    client->on(event,[=](SIOClient* client,std::string msg){
        msg.erase(0,1);
        msg.erase(msg.size()-1,1);
        while(msg.find("\\")!=std::string::npos)
        {
            msg.erase(msg.find("\\"),1);
        }
        callback(client,msg);
    });
}

void SocketIOClient::send(char *event,char* msg)
{
    client->emit(event,msg);
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
