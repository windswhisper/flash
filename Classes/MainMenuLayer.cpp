#include "MainMenuLayer.h"

bool MainMenuLayer::init()
{

	this->sp = Sprite::create("img/mainmenu/sp.png");
	this->sp->setPosition(500, 500);
	this->sp->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1,1.1), ScaleTo::create(0.4, 1),NULL)));
	this->sp->runAction(RepeatForever::create(Sequence::create(RotateBy::create(2, Vec3(0, 40, 0)), RotateBy::create(4, Vec3(0, -80, 0))	, RotateBy::create(2, Vec3(0, 40, 0)), NULL)));
	this->addChild(this->sp);
    
    this->btnClassic = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn.png", CC_CALLBACK_0(MainMenuLayer::classic, this));
    
    auto textClassic = Sprite::create();
    
    this->btnClassic->addChild(textClassic);
    
    this->btnClassic->setPosition(1800, 800);
    
    this->btnDuel = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn.png", CC_CALLBACK_0(MainMenuLayer::classic, this));
    
    this->btnDuel->setPosition(1800, 600);
    
    this->btnShop = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn.png", CC_CALLBACK_0(MainMenuLayer::classic, this));
    
    this->btnShop->setPosition(1800, 400);
    
    this->btnSetting = MenuItemImage::create("img/mainmenu/btn.png", "img/mainmenu/btn.png", CC_CALLBACK_0(MainMenuLayer::classic, this));
    
    this->btnSetting->setPosition(1800, 200);
    
    
    Menu* menu = Menu::create(btnClassic, btnDuel, btnShop, btnSetting, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    return true;
}

void MainMenuLayer::classic()
{
    
}
