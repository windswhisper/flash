#include "PauseLayer.h"
#include "GameLayer.h"
#include "SongsLayer.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool PauseLayer::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();

	pauseBg = Sprite::create("img/pause/pauseBg.png");

	pauseBg->setPosition(visiblesize.width/2,visiblesize.height/2);

	this->addChild(pauseBg);


	btn_continue = MenuItemImage::create("img/pause/button.png", "img/pause/button_p.png", CC_CALLBACK_0(PauseLayer::continuePlay,this));

	btn_continue->setPosition(visiblesize.width/2,visiblesize.height*0.8);

	auto continueSprite = Sprite::create("img/pause/continue.png");

	continueSprite->setPosition(btn_continue->getContentSize().width/2,btn_continue->getContentSize().height/2);

	btn_continue->addChild(continueSprite);


	btn_playAgain = MenuItemImage::create("img/pause/button.png", "img/pause/button_p.png", CC_CALLBACK_0(PauseLayer::playAgain, this));

	btn_playAgain->setPosition(visiblesize.width / 2, visiblesize.height*0.5);

	auto playAgainSprite = Sprite::create("img/pause/playAgain.png");

	playAgainSprite->setPosition(btn_playAgain->getContentSize().width / 2, btn_playAgain->getContentSize().height / 2);

	btn_playAgain->addChild(playAgainSprite);


	btn_back = MenuItemImage::create("img/pause/button.png", "img/pause/button_p.png", CC_CALLBACK_0(PauseLayer::back, this));

	btn_back->setPosition(visiblesize.width / 2, visiblesize.height*0.2);

	auto backSprite = Sprite::create("img/pause/back.png");

	backSprite->setPosition(btn_back->getContentSize().width / 2, btn_back->getContentSize().height / 2);

	btn_back->addChild(backSprite);


	Menu* menu = Menu::create(btn_continue, btn_playAgain, btn_back,NULL);

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

void PauseLayer::continuePlay()
{
	Director::getInstance()->resume();
	
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	this->removeFromParent();
}

void PauseLayer::playAgain()
{
	this->getParent()->getParent()->addChild(GameLayer::createWithId(songId,name,songdiff,pkMode));

	this->getParent()->removeFromParent();

	Director::getInstance()->resume();

}

void PauseLayer::back()
{
	this->getParent()->getParent()->addChild(SongsLayer::create());

	this->getParent()->removeFromParent();

	Director::getInstance()->resume();
}

PauseLayer* PauseLayer::createWithSong(int id,char* name, char* diff, int pkMode)
{
	auto pauseLayer = PauseLayer::create();

	pauseLayer->songId = id;
    
	pauseLayer->pkMode = pkMode;
    
    strcpy(pauseLayer->name, name);
    
	strcpy(pauseLayer->songdiff, diff);

	return pauseLayer;

}
