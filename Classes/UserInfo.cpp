#include "UserInfo.h"
#include "SocketIOClient.h"

UserInfo* UserInfo::getInstance()
{
    if(_userInfo==NULL)
    {
        _userInfo = new UserInfo();
        _userInfo->load();
    }
    return _userInfo;
}

void UserInfo::load()
{
    SocketIOClient::getInstance()->send("userInfo", "");
    SocketIOClient::getInstance()->lock();
    SocketIOClient::getInstance()->listen("userInfoRes", [=](SIOClient* client, std::string msg){
        
        rapidjson::Document doc;
        doc.Parse<0>(msg.c_str());
        
        strcpy(this->username,doc["username"].GetString());
        this->coin = doc["coin"].GetInt();
        this->item[0] = doc["itemM"].GetInt();
        this->item[1] = doc["itemG"].GetInt();
        this->item[2] = doc["itemR"].GetInt();
        this->skill[0] = doc["skillL"].GetInt();
        this->skill[1] = doc["skillC"].GetInt();
        this->skill[2] = doc["skillI"].GetInt();
        
        SocketIOClient::getInstance()->unlock();
    });

}
