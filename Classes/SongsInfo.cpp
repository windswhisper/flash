#include "SongsLayer.h"

#include "MainMenuLayer.h"

bool SongsLayer::init()
{
    
    this->btn_mainmenu = MenuItemImage::create("img/selectsongs/btn_mainmenu.png", "img/selectsongs/btn_mainmenu_p.png", CC_CALLBACK_0(SongsLayer::backToMenu, this));
    
    this->btn_mainmenu->setPosition(250,973+300);
    
    this->btn_mainmenu->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,-300)))),NULL));
    
    auto ringL = Sprite::create("img/selectsongs/ring.png");
    
    ringL->setPosition(130,98);
    
    ringL->runAction(RepeatForever::create(RotateBy::create(4, 360)));
    
    this->btn_mainmenu->addChild(ringL);
    
    
    
    this->btn_setting = MenuItemImage::create("img/selectsongs/btn_setting.png", "img/selectsongs/btn_setting_p.png", CC_CALLBACK_0(SongsLayer::setting, this));
    
    this->btn_setting->setPosition(1670,973+300);
    
    this->btn_setting->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,-300)))),NULL));
    
    auto ringR = Sprite::create("img/selectsongs/ring.png");
    
    ringR->setPosition(357,96);
    
    ringR->runAction(RepeatForever::create(RotateBy::create(4, 360)));
    
    this->btn_setting->addChild(ringR);
    
    
    Menu* menu = Menu::create(btn_mainmenu, btn_setting, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    auto playButton = Sprite::create("img/selectsongs/btn_play.png");
    
    playButton->setPosition(1800,120);
    
    playButton->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1,1.1), ScaleTo::create(0.4, 1),NULL)));
    
    this->addChild(playButton);
    
    return true;
}

void SongsLayer::backToMenu()
{
    this->getParent()->addChild(MainMenuLayer::create());
    
    this->close();

}

void SongsLayer::setting()
{
    
}

void SongsLayer::close()
{
    this->btn_mainmenu->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),NULL));
    this->btn_setting->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),CallFunc::create(CC_CALLBACK_0(SongsLayer::removeFromParent, this)),NULL));
}
