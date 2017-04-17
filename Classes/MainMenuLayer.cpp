#include "MainMenuLayer.h"
#include "UserInfo.h"
#include "SongsInfo.h"
#include "SongsLayer.h"
#include "shop\ShopLayer.h"
#include "PK/PKSelectDiff.h"
#include "shop/ShopLayer.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool MainMenuLayer::init()
{
    //if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    //    SimpleAudioEngine::getInstance()->playBackgroundMusic("TheFatRat - Unity.mp3",true);

    this->sp = Sprite::create("img/mainmenu/sp.png");
    this->sp->setPosition(500, 500);
    this->sp->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(60/105.3*0.2,1.1), ScaleTo::create(60/105.3*0.8, 1),NULL)));//《Unity》bpm为105.3
    this->sp->runAction(RepeatForever::create(Sequence::create(RotateBy::create(2, Vec3(0, 40, 0)), RotateBy::create(4, Vec3(0, -80, 0))	, RotateBy::create(2, Vec3(0, 40, 0)), NULL)));
    this->sp->setOpacity(0);
    this->sp->runAction(FadeTo::create(1, 255));
    this->addChild(this->sp);
    
    this->btnClassic = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn_p.png", CC_CALLBACK_0(MainMenuLayer::classic, this));
    
    auto textClassic = Sprite::create("img/mainmenu/classic.png");
    
    textClassic->setPosition(400,110);
    
    this->btnClassic->addChild(textClassic);
    
    this->btnClassic->setPosition(1530+800, 780);
    
    this->btnClassic->runAction(Sequence::create(DelayTime::create(0.1f),(EaseSineOut::create(MoveBy::create(1,Vec2(-800,0)))),NULL));
    
    
    this->btnDuel = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn_p.png", CC_CALLBACK_0(MainMenuLayer::duel, this));
    
    auto textDuel= Sprite::create("img/mainmenu/duel.png");
    
    textDuel->setPosition(380,110);
    
    this->btnDuel->addChild(textDuel);
    
    this->btnDuel->setPosition(1630+800,602);
    
    this->btnDuel->runAction(Sequence::create(DelayTime::create(0.2f),(EaseSineOut::create(MoveBy::create(1,Vec2(-800,0)))),NULL));
    
    
    this->btnShop = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn_p.png", CC_CALLBACK_0(MainMenuLayer::shop, this));
    
    auto textShop= Sprite::create("img/mainmenu/shop.png");
    
    textShop->setPosition(330,110);
    
    this->btnShop->addChild(textShop);
    
    this->btnShop->setPosition(1730+800, 424);
    
    this->btnShop->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(-800,0)))),NULL));
    
    
    this->btnSetting = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn_p.png", CC_CALLBACK_0(MainMenuLayer::setting, this));
    
    auto textSetting= Sprite::create("img/mainmenu/setting.png");
    
    textSetting->setPosition(300,110);
    
    this->btnSetting->addChild(textSetting);
    
    this->btnSetting->setPosition(1830+800, 246);
    
    this->btnSetting->runAction(Sequence::create(DelayTime::create(0.4f),(EaseSineOut::create(MoveBy::create(1,Vec2(-800,0)))),NULL));
    
    
    Menu* menu = Menu::create(btnClassic, btnDuel, btnShop, btnSetting, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    SongsInfo::getInstance();
    UserInfo::getInstance();
    
    
    return true;
}

void MainMenuLayer::classic()
{
    this->close(CallFunc::create([=](){
        this->getParent()->addChild(SongsLayer::create());
    }));
}

void MainMenuLayer::duel()
{
	this->close(CallFunc::create([=](){
		this->getParent()->addChild(PKSelectDiff::create());
	}));
}
void MainMenuLayer::shop()
{
	this->close(CallFunc::create([=](){
		this->getParent()->addChild(ShopLayer::create());
	}));
}
void MainMenuLayer::setting()
{
}

void MainMenuLayer::close(CallFunc* callfunc)
{
    this->getEventDispatcher()->removeEventListenersForTarget(this,true);
    
    this->btnClassic->runAction(Sequence::create(DelayTime::create(0.1f),(EaseSineOut::create(MoveBy::create(0.6f,Vec2(1000,0)))),NULL));
    this->btnDuel->runAction(Sequence::create(DelayTime::create(0.2f),(EaseSineOut::create(MoveBy::create(0.6f,Vec2(1000,0)))),NULL));
    this->btnShop->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(0.6f,Vec2(1000,0)))),NULL));
    this->btnSetting->runAction(Sequence::create(DelayTime::create(0.4f),(EaseSineOut::create(MoveBy::create(0.6f,Vec2(1000,0)))),callfunc,CallFunc::create(CC_CALLBACK_0(MainMenuLayer::removeFromParent, this)),NULL));
    
    this->sp->runAction(FadeTo::create(0.5f, 0));
    
}
