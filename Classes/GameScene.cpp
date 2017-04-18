#include "GameScene.h"
#include "GameLayer.h"
#include "LoginPanel.h"
#include "SocketIOClient.h"

GameScene* GameScene::getInstance()
{
    return _gamescene;
}
bool GameScene::init()
{
    _gamescene = this;
    
    this->bg = Sprite::create("img/bg.png");
    
    this->bg->setPosition(960, 540);
    
    this->bg->setGlobalZOrder(-1);
    
    this->addChild(this->bg);
    
    this->addChild(LoginPanel::create());
    

    
    this->lockLayer = Layer::create();
    
    ringIn = Sprite::create("img/loading/loadingRingIn.png");
    
    ringIn->setPosition(100,100);
    
    lockLayer->addChild(ringIn);
    
    ringOut = Sprite::create("img/loading/loadingRingOut.png");
    
    ringOut->setPosition(100,100);
    
    lockLayer->addChild(ringOut);
    
    lockText = Sprite::create("img/loading/loadingText.png");
    
    lockText->setPosition(340,70);
    
    lockLayer->addChild(lockText);
    
    this->addChild(this->lockLayer,127);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,lockLayer);
    
    this->lockCount = 1;
    
    this->unlockScreen();
    
    
    SocketIOClient::getInstance()->connect();
    
    return true;
}

void GameScene::lockScreen()
{
    lockCount++;
    
    if(lockCount>1)return;
    
    this->addChild(this->lockLayer,127);
    
    ringIn->runAction(RepeatForever::create(RotateBy::create(4, 360)));
    
    ringOut->runAction(RepeatForever::create(RotateBy::create(4, -360)));
    
}

void GameScene::unlockScreen()
{
    lockCount--;
    
    if(lockCount>0)return;
    
    this->lockLayer->retain();
    this->lockLayer->removeFromParent();
}
