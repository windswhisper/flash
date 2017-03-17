#include "SongsLayer.h"

#include "MainMenuLayer.h"
#include "SongsListView.h"


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
    
    this->btn_setting->runAction(Sequence::create(DelayTime::create(0.5f),(EaseSineOut::create(MoveBy::create(0.5f,Vec2(0,-300)))),NULL));
    
    auto ringR = Sprite::create("img/selectsongs/ring.png");
    
    ringR->setPosition(357,96);
    
    ringR->runAction(RepeatForever::create(RotateBy::create(4, 360)));
    
    this->btn_setting->addChild(ringR);
    
    
    Menu* menu = Menu::create(btn_mainmenu, btn_setting, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    auto playButton = Sprite::create("img/selectsongs/btn_play.png");
    
    playButton->setPosition(1800,120);
    
    playButton->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1f,1.1f), ScaleTo::create(0.4f, 1),NULL)));
    
    //this->addChild(playButton);
    
    
    this->songsList = SongsListView::create();
    
    this->songsList->setPosition(375-800,725);
    
    this->songsList->runAction(Sequence::create(DelayTime::create(0.1f),(EaseSineOut::create(MoveBy::create(1,Vec2(800,0)))),NULL));
    
    this->addChild(this->songsList);
    
    
    this->coverScreen = Node::create();
    
    this->coverScreen->setPosition(1360,450);
    
    this->coverScreen->setScale(1,0);
    
    this->coverScreen->runAction(Sequence::create(DelayTime::create(0.5f),EaseSineOut::create(ScaleTo::create(0.5f, 1)),NULL));
    
    this->addChild(coverScreen);
    
    auto coverBg = Sprite::create("img/selectsongs/frame.png");
    
    this->coverScreen->addChild(coverBg);
    
    this->songCover = Sprite::create("img/1.jpg");
    
    this->songCover->setOpacity(0);
    
    this->songCover->runAction(Sequence::create(DelayTime::create(1),FadeTo::create(0.5f,255),NULL));
    
    this->songCover->setScale(600.0f/this->songCover->getContentSize().height);
    
    this->coverScreen->addChild(this->songCover);
    
    return true;
}

void SongsLayer::backToMenu()
{
    
    this->close(CallFunc::create([=]()
    {
        this->getParent()->addChild(MainMenuLayer::create());
    }));

}

void SongsLayer::setting()
{
    this->changerCover("img/2.jpg");
}

void SongsLayer::close(CallFunc* callfunc)
{
    this->getEventDispatcher()->removeEventListenersForTarget(this,true);
    
    this->songCover->runAction(FadeTo::create(0.5f,0));
    this->coverScreen->runAction(Sequence::create(DelayTime::create(0.5f),EaseSineIn::create(ScaleTo::create(0.5f, 1,0)),NULL));
    this->songsList->runAction(Sequence::create(DelayTime::create(0.1f),(EaseSineOut::create(MoveBy::create(1,Vec2(-800,0)))),NULL));
    this->btn_mainmenu->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),NULL));
    this->btn_setting->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),callfunc,CallFunc::create(CC_CALLBACK_0(SongsLayer::removeFromParent, this)),NULL));
}

void SongsLayer::changerCover(const char* fileName)
{
    this->songCover->runAction(Sequence::create(FadeTo::create(0.3f,0),CallFunc::create([=](){this->songCover->setTexture(fileName);}),FadeTo::create(0.3f,255), NULL));
}
