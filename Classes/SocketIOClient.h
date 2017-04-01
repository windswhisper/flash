#ifndef __SOCKET_IO_CLIENT_H__
#define __SOCKET_IO_CLIENT_H__

#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "network/SocketIO.h"

USING_NS_CC;
using namespace cocos2d::network;

class SocketIOClient : public SocketIO::SIODelegate
{
    SocketIOClient();
    ~SocketIOClient();
public:
    static SocketIOClient* getInstance();
    
    void connect();
    
    void listen(char* event,std::function<void(SIOClient*,std::string msg)> callback);
    
    void send(char* event,char* msg);
    
    void onConnect(SIOClient* client);
    
    void onMessage(SIOClient* client, const std::string& data);
    
    void onError(SIOClient* client, const std::string& data);
    
    void onClose(SIOClient* client);
    
    SIOClient* client;
    
};

static SocketIOClient* _socketIOClient=NULL;

#endif
