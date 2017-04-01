#include "SongsLayer.h"

#include "MainMenuLayer.h"
#include "SongsListView.h"
#include "GameLayer.h"
#include "RankingList.h"
#include "ItemSelection.h"

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
    
    
    playButton = MenuItemImage::create("img/selectsongs/btn_play.png","img/selectsongs/btn_play.png",CC_CALLBACK_0(SongsLayer::play, this));
    
    playButton->setPosition(1800+800,120);
    
    playButton->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1f,1.1f), ScaleTo::create(0.4f, 1),NULL)));
    
    
    btn_back = MenuItemImage::create("img/selectsongs/back.png","back.png",CC_CALLBACK_0(SongsLayer::backToList, this));
    
    btn_back->setPosition(100,450);
    
    btn_back->runAction(RepeatForever::create(Sequence::create(FadeTo::create(1.0f,72), FadeTo::create(1.0f, 255),NULL)));
    
    btn_back->setVisible(false);
    
    Menu* menu = Menu::create(btn_mainmenu, btn_setting,playButton,btn_back, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);

    
    
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

	/**************************************************************************************************/
	this->rankingList = RankingList::create();

	this->rankingList->setPosition(1220 + 800, 280);

//	this->rankList->runAction(Sequence::create(DelayTime::create(1), FadeTo::create(0.5f, 255), NULL));
    
	this->addChild(this->rankingList);

	this->rankingList->setVisible(false);

/***
	
*******	µÀ¾ßÑ¡Ôñ************

***/

	this->itemSelection = ItemSelection::create();

	this->itemSelection->setPosition(1408 + 800,680);

	this->itemSelection->setVisible(false);

	this->addChild(this->itemSelection);

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
}

void SongsLayer::close(CallFunc* callfunc)
{
    this->getEventDispatcher()->removeEventListenersForTarget(this,true);
    
    this->playButton->runAction(FadeTo::create(0.5f,0));
    this->songCover->runAction(FadeTo::create(0.5f,0));
    this->coverScreen->runAction(Sequence::create(DelayTime::create(0.5f),EaseSineIn::create(ScaleTo::create(0.5f, 1,0)),NULL));
    this->songsList->runAction(Sequence::create(DelayTime::create(0.1f),(EaseSineOut::create(MoveBy::create(1,Vec2(-800,0)))),NULL));
    this->btn_mainmenu->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),NULL));
    this->btn_setting->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),callfunc,CallFunc::create(CC_CALLBACK_0(SongsLayer::removeFromParent, this)),NULL));
}

void SongsLayer::changeCover(int id)
{
    const char* fileName = "img/2.jpg";
    
    this->songCover->runAction(Sequence::create(FadeTo::create(0.3f,0),CallFunc::create([=](){this->songCover->setTexture(fileName);}),FadeTo::create(0.3f,255), NULL));
}

void SongsLayer::selectSong(int id, int diff)
{
    auto action = EaseSineOut::create(MoveBy::create(1.0f, Vec2(-800,0)));

	this->songsList->runAction(action->clone());

	this->rankingList->setVisible(true);

	this->rankingList->runAction(Sequence::create(action, CallFunc::create([=](){this->btn_back->setVisible(true); }), NULL)); //*****************************************************88
    
	this->itemSelection->setVisible(true);

	this->itemSelection->runAction(action->clone());

    this->coverScreen->runAction(action->clone());
    
    this->playButton->runAction(action->clone());
}

void SongsLayer::backToList()
{
    auto action = EaseSineOut::create(MoveBy::create(1.0f, Vec2(800,0)));
    
    this->songsList->runAction(action->clone());
    
    this->coverScreen->runAction(action->clone());

	this->rankingList->runAction(Sequence::create(action->clone(), CallFunc::create([=](){this->rankingList->setVisible(false); }), NULL));

	this->itemSelection->runAction(Sequence::create(action, CallFunc::create([=](){this->itemSelection->setVisible(false); }), NULL));
    
    this->playButton->runAction(action->clone());
    
    this->btn_back->setVisible(false);
}

void SongsLayer::play()
{
    this->close(CallFunc::create([=]{
        this->getParent()->addChild(GameLayer::create());
    }));
}
