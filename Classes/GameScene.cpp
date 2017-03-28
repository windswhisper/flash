#include "GameScene.h"

#include "GameLayer.h"
#include "LoginPanel.h"

#include "SocketIOClient.h"

bool GameScene::init()
{
    this->bg = Sprite::create("img/bg.png");
    
    this->bg->setPosition(960, 540);
    
    this->bg->setGlobalZOrder(-1);
    
    this->addChild(this->bg);
    
    this->addChild(LoginPanel::create());
    
    SocketIOClient::getInstance()->connect();
    
    return true;
}
