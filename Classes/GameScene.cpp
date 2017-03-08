#include "GameScene.h"

#include "GameLayer.h"
#include "WelcomeLayer.h"

bool GameScene::init()
{
    this->addChild(WelcomeLayer::create());
    
    return true;
}
