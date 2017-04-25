#include "SongsLayer.h"

#include "MainMenuLayer.h"
#include "SongsListView.h"
#include "GameLayer.h"
#include "RankingList.h"
#include "ItemSelection.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


bool SongsLayer::init()
{
    this->isSelected = false;
    
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

    
    
	this->rankingList = RankingList::create();

	this->rankingList->setPosition(1220 , 280-1000);
    
    this->rankingList->setCascadeOpacityEnabled(true);
    
	this->addChild(this->rankingList);



	this->itemSelection = ItemSelection::create();

	this->itemSelection->setPosition(1408 + 1000,680);

    this->itemSelection->setCascadeOpacityEnabled(true);
    
	this->itemSelection->setOpacity(0);

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
    
    this->btn_back->setVisible(false);
    this->playButton->runAction(FadeTo::create(0.5f,0));
    this->songCover->runAction(FadeTo::create(0.5f,0));
    this->coverScreen->runAction(Sequence::create(DelayTime::create(0.5f),EaseSineIn::create(ScaleTo::create(0.5f, 1,0)),NULL));
    this->songsList->runAction(Sequence::create(DelayTime::create(0.1f),(EaseSineOut::create(MoveBy::create(1,Vec2(-800,0)))),NULL));
    this->btn_mainmenu->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),NULL));
    this->rankingList->runAction(Sequence::create(Spawn::create(EaseSineOut::create(MoveBy::create(0.4f, Vec2(0,-1000))),FadeTo::create(0.4f, 0), NULL), NULL));
    this->itemSelection->runAction(Sequence::create(Spawn::create(EaseSineOut::create(MoveBy::create(0.4f, Vec2(1000,0))),FadeTo::create(0.4f, 0), NULL), NULL));
    this->btn_setting->runAction(Sequence::create(DelayTime::create(0.3f),(EaseSineOut::create(MoveBy::create(1,Vec2(0,300)))),callfunc,CallFunc::create(CC_CALLBACK_0(SongsLayer::removeFromParent, this)),NULL));
}

void SongsLayer::changeCover(int id,char* name)
{
    
    this->songCover->runAction(Sequence::create(FadeTo::create(0.3f,0),CallFunc::create([=](){
        char fileName[64];
        sprintf(fileName,"songs/%d/cover.jpg",id);
        this->songCover->setTexture(fileName);
        
        sprintf(fileName, "songs/%d/%s.mp3",id,name);
        SimpleAudioEngine::getInstance()->playBackgroundMusic(fileName,true);
    }),FadeTo::create(0.3f,255), NULL));
}

void SongsLayer::selectSong(int id,char* name, char* diff)
{
    if(isSelected)return;
    
    isSelected = true;
    
    this->songId = id;
    
    strcpy(songDiff, diff);
    
    strcpy(songName, name);
    
    
    ((RankingList*)this->rankingList)->load(id,diff);
    
    auto action = EaseSineOut::create(MoveBy::create(1.0f, Vec2(-800,0)));

	this->songsList->runAction(action->clone());
    
    this->rankingList->runAction(Sequence::create(DelayTime::create(1.0f),Spawn::create(EaseSineOut::create(MoveBy::create(0.6f, Vec2(0,1000))),FadeTo::create(0.6f, 255), NULL), NULL));
    
    this->itemSelection->runAction(Sequence::create(DelayTime::create(0.8f),Spawn::create(EaseSineOut::create(MoveBy::create(0.4f, Vec2(-1000,0))),FadeTo::create(0.4f, 255), NULL), NULL));

    this->coverScreen->runAction(action->clone());
    
    this->playButton->runAction(Sequence::create(action->clone(),CallFunc::create([=](){
        this->btn_back->setVisible(true);
    }),NULL));
 
}
void SongsLayer::backToList()
{
    if(!isSelected)return;
    
    isSelected=false;
    
    auto action = EaseSineOut::create(MoveBy::create(1.0f, Vec2(800,0)));
    
    this->songsList->runAction(action->clone());
    
    this->coverScreen->runAction(action->clone());

    this->rankingList->runAction(Sequence::create(Spawn::create(EaseSineOut::create(MoveBy::create(0.4f, Vec2(0,-1000))),FadeTo::create(0.4f, 0), NULL), NULL));
    
    this->itemSelection->runAction(Sequence::create(Spawn::create(EaseSineOut::create(MoveBy::create(0.4f, Vec2(1000,0))),FadeTo::create(0.4f, 0), NULL), NULL));
    
    this->playButton->runAction(action->clone());
    
    this->btn_back->setVisible(false);
}

void SongsLayer::play()
{
    this->close(CallFunc::create([=]{
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        this->getParent()->addChild(GameLayer::createWithId(this->songId , this->songDiff, 0));
    }));
}
