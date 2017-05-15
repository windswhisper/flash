#include "FailedLayer.h"
#include "GameLayer.h"
#include "SongsLayer.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool FailedLayer::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();

	pauseBg = Sprite::create("img/pause/pauseBg.png");

	pauseBg->setPosition(visiblesize.width/2,visiblesize.height/2);

	this->addChild(pauseBg);


	failedLabel = Sprite::create("img/pause/fail.png");

	failedLabel->setPosition(visiblesize.width / 2, visiblesize.height*0.7);

	this->addChild(failedLabel);


	btn_playAgain = MenuItemImage::create("img/pause/button.png", "img/pause/button_p.png", CC_CALLBACK_0(FailedLayer::playAgain, this));

	btn_playAgain->setPosition(visiblesize.width / 2, visiblesize.height*0.4);

	auto playAgainSprite = Sprite::create("img/pause/playAgain.png");

	playAgainSprite->setPosition(btn_playAgain->getContentSize().width / 2, btn_playAgain->getContentSize().height / 2);

	btn_playAgain->addChild(playAgainSprite);


	btn_back = MenuItemImage::create("img/pause/button.png", "img/pause/button_p.png", CC_CALLBACK_0(FailedLayer::back, this));

	btn_back->setPosition(visiblesize.width / 2, visiblesize.height*0.2);

	auto backSprite = Sprite::create("img/pause/back.png");

	backSprite->setPosition(btn_back->getContentSize().width / 2, btn_back->getContentSize().height / 2);

	btn_back->addChild(backSprite);


	Menu* menu = Menu::create(btn_playAgain, btn_back,NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu,1);

    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](Touch* touch,Event* event){
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
	return true;
}

void FailedLayer::playAgain()
{
	this->getParent()->getParent()->addChild(GameLayer::createWithId(songId,name,songdiff,pkMode));

	this->getParent()->removeFromParent();

	Director::getInstance()->resume();

}

void FailedLayer::back()
{
	this->getParent()->getParent()->addChild(SongsLayer::create());

	this->getParent()->removeFromParent();

	Director::getInstance()->resume();
}

FailedLayer* FailedLayer::createWithSong(int id, char* name, char* diff, int pkMode)
{
	auto failedLayer = FailedLayer::create();

	failedLayer->songId = id;
    
	failedLayer->pkMode = pkMode;
    
	strcpy(failedLayer->name, name);
    
	strcpy(failedLayer->songdiff, diff);

	return failedLayer;

}
