#include "GameScene.h"

#include "GameLayer.h"
#include "WelcomeLayer.h"

bool GameScene::init()
{
    this->bg = Sprite::create("img/bg.png");
    
    this->bg->setPosition(960, 540);
    
    this->bg->setGlobalZOrder(-1);
    
    this->addChild(this->bg);
    
    this->addChild(WelcomeLayer::create());
    
    return true;
}
