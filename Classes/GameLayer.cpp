#include "GameLayer.h"
#include "SongsInfo.h"
#include "SocketIOClient.h"
#include "GameOver.h"
#include "PauseLayer.h"
#include "SongsLayer.h"
#include "SettingData.h"

#include  <iostream>
#include  <fstream>
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

int RATE_SCORE[4] = {0,100,80,40};//{miss,cool,good,poor}
int RATE_HP[4] = {-10,4,2,-4};
int RATE_STD[4] = {0,40,80,100};
int MAX_HP = 100;
int MAX_POWER = 100;
float COMBO_BUFF = 2.0f;

void Note::remove()
{
    this->removeFromParent();
    _gamelayer->tags[this->x].eraseObject(this);
}



bool SimpleNote::init()
{
    return true;
}
SimpleNote* SimpleNote::createSimpleNote(int x, int t, int type, int endt)
{
    SimpleNote* note = SimpleNote::create();
    
    note->x = x;
    note->t = t;
    note->type = type;
    note->endt = endt;
    
    return note;
}
void SimpleNote::display()
{
    this->p = Sprite::create("img/game/note.png");
    
    this->runAction(Sequence::create(MoveBy::create(_gamelayer->offset+0.2f, Vec2(0,-3000*(_gamelayer->offset+0.2f)/_gamelayer->offset)),CallFunc::create([=]{this->miss();}),NULL));
    
    this->addChild(this->p);
}
void SimpleNote::miss()
{
    _gamelayer->miss(this->x);
    this->remove();
}
void SimpleNote::click()
{
    _gamelayer->playAnimate(this->x, 0);
    this->stopAllActions();
    this->removeFromParent();
    _gamelayer->tags[this->x].eraseObject(this);
}
void SimpleNote::release()
{
}



bool LongNote::init()
{
    return true;
}
LongNote* LongNote::createLongNote(int x, int t, int type, int endt)
{
    LongNote* note = LongNote::create();
    
    note->x = x;
    note->t = t;
    note->type = type;
    note->endt = endt;
    
    note->tSum = 0;
    note->status = 0;
    
    return note;
}
void LongNote::display()
{
    auto p = Sprite::create("img/game/longnoteB.png");
    
    this->addChild(p);
    
    this->pics.pushBack(p);
    
    int n=1;
    
    while(78*n<2*(this->endt-this->t))
    {
        p = Sprite::create("img/game/longnoteM.png");
        
        p->setPosition(0,78*n);
        
        this->addChild(p);
        
        this->pics.pushBack(p);
        
        n++;
    }
    
    p = Sprite::create("img/game/longnoteE.png");
    
    p->setPosition(0,2*(this->endt-this->t));
    
    this->addChild(p);
    
    this->pics.pushBack(p);
    
    this->pics.reverse();
    
    this->runAction(Sequence::create(MoveBy::create(_gamelayer->offset+0.2f, Vec2(0,-3000*(_gamelayer->offset+0.2f)/_gamelayer->offset)),CallFunc::create([=]{this->miss();}),MoveBy::create((this->endt-this->t)/1000.0f, Vec2(0,-2*(this->endt-this->t))),CallFunc::create([=]{this->remove();}),NULL));
}
void LongNote::miss()
{
    if(this->status == 0)
    {
        _gamelayer->miss(this->x);
        this->status = 2;
    }
}
void LongNote::click()
{    if(this->status == 0)
{
    this->status = 1;
    _gamelayer->playAnimate(this->x, 1);
    this->scheduleUpdate();
}
}
void LongNote::release()
{
    if(this->status == 1)
    {
        _gamelayer->hitEffect[this->x]->stopAllActions();
        _gamelayer->hitEffect[this->x]->setSpriteFrame("space.png");
        _gamelayer->miss(this->x);
        this->status = 2;
    }
}
void LongNote::update(float dt)
{
    
    if(this->status!=1)return;
    
    if(pics.size()>0&&pics.at(pics.size()-1)->getPositionY()+this->getPositionY()<_gamelayer->key1Pos.y)
    {
        pics.at(pics.size()-1)->removeFromParent();
        pics.popBack();
    }
    
    if((_gamelayer->t-_gamelayer->offset)*1000>this->endt)this->finish();
    
    this->tSum+=dt;
    if(tSum<0.25f)return;
    tSum-=0.25f;
    
    _gamelayer->getRate(1);
}
void LongNote::finish()
{
    this->status=3;
    this->removeAllChildren();
    _gamelayer->hitEffect[this->x]->stopAllActions();
    _gamelayer->hitEffect[this->x]->setSpriteFrame("space.png");
}


bool GameLayer::init()
{
    _gamelayer = this;
    
    this->speed = 1.5;
    this->offset = 2 / speed;
    
    this->key1Pos = Vec2(229,350);
    this->keyDis = 318;
    
    this->rateCount[0] = 0;
    this->rateCount[1] = 0;
    this->rateCount[2] = 0;
    this->rateCount[3] = 0;
    this->score = 0;
    this->maxCombo = 0;
    this->combo = 0;
    
    this->hp = 100;
    
    auto setting = SettingData::getInstance();
    
    for(int i=0;i<8;i++)
    {
        printf("%d",setting->itemSwitch[i]);
        if(!setting->disableItem)
            this->itemOn[i] = setting->itemSwitch[i];
        else
            this->itemOn[i] = false;
        this->itemCount[i] = 10;
        
        printf("%d",itemOn[i]);
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/game/hit.plist");
    AnimationCache::getInstance()->addAnimationsWithFile("img/game/hit_ani.plist");
    AnimationCache::getInstance()->addAnimationsWithFile("img/game/lhit_ani.plist");
    
    root = Node::create();
    
    this->addChild(root);
    
    board = Sprite::create("img/game/board.png");
    
    board->setRotation3D(Vec3(-40,0,0));
    
    board->setCascadeOpacityEnabled(true);
    
    board->setOpacity(0);
    
    board->runAction(FadeTo::create(0.4f, 255));
    
    board->setScale(0.25);
    
    board->setPosition(0,250);
    
    root->addChild(board);
    
    root->setPosition(960,540);
    
    root->setScale(2);
    
    this->comboLabel = LabelAtlas::create("","img/game/combo.png",184,206,'0');
    
    this->comboLabel->setPosition(960,700);
    
    this->addChild(this->comboLabel);
    
    this->scoreLabel = Label::createWithSystemFont("0000000", "Arial", 80);
    
    this->scoreLabel->setPosition(1920,1080);
    
    this->scoreLabel->setAnchorPoint(Vec2(1,1));
    
    this->addChild(this->scoreLabel);
    
    for(int i=0;i<4;i++)
    {
        this->key[i] = Sprite::create("img/game/stdline.png");
        
        this->key[i]->setPosition(key1Pos+Vec2(keyDis*i,0));
        
        this->board->addChild(this->key[i]);
        
        
        this->hitEffect[i] = Sprite::createWithSpriteFrameName("space.png");
        
        this->hitEffect[i]->setPosition(key1Pos+Vec2(keyDis*i,0));
        
        this->hitEffect[i]->setBlendFunc(BlendFunc({GL_ONE,GL_ONE}));
        
        this->hitEffect[i]->setScale(1.5f);
        
        this->board->addChild(this->hitEffect[i]);
        
        
        this->pressLight[i] = Sprite::create("img/game/press.png");
        
        this->pressLight[i]->setPosition(key1Pos+Vec2(keyDis*i,400));
        
        this->pressLight[i]->setOpacity(0);
        
        this->board->addChild(this->pressLight[i]);
        
        
    }
	
		/*btn_pause = MenuItemImage::create("img/game/btn_pause.png", "img/game/btn_pause_p.png", CC_CALLBACK_0(GameLayer::gamePause, this));

		btn_pause->setPosition(Vec2(btn_pause->getContentSize().width / 2, 980));


		auto ring = Sprite::create("img/selectsongs/ring.png");

		ring->setPosition(130, 100);

		ring->runAction(RepeatForever::create(RotateBy::create(4, 360)));

		btn_pause->addChild(ring);


		Menu* menu = Menu::create(btn_pause, NULL);

		menu->setPosition(Point::ZERO);

		this->addChild(menu);*/

    
    this->hpFrame = Sprite::create("img/game/hpFrame.png");
    
    this->hpFrame->setPosition(1920-100+400,540);
    
    this->hpFrame->runAction(EaseSineOut::create(MoveBy::create(0.4f, Vec2(-400,0))));
    
    this->addChild(hpFrame);
    
    this->hpBar = ProgressTimer::create(Sprite::create("img/game/hpBar.png"));
    
    this->hpBar->setType(ProgressTimer::Type::BAR);
    
    this->hpBar->setMidpoint(Point(1, 0));
    
    this->hpBar->setBarChangeRate(Point(0, 1));
    
    this->hpBar->setPercentage(100);
    
    this->hpBar->setPosition(93,310);
    
    this->hpFrame->addChild(hpBar);
    
    this->comboFrame = Sprite::create("img/game/comboFrame.png");
    
    this->comboFrame->setPosition(100-400,540);
    
    this->comboFrame->runAction(EaseSineOut::create(MoveBy::create(0.4f, Vec2(400,0))));
    
    this->addChild(comboFrame);
    
    this->comboBar = ProgressTimer::create(Sprite::create("img/game/comboBar.png"));
    
    this->comboBar->setType(ProgressTimer::Type::BAR);
    
    this->comboBar->setMidpoint(Point(1, 0));
    
    this->comboBar->setBarChangeRate(Point(0, 1));
    
    this->comboBar->setPercentage(0);
    
    this->comboBar->setPosition(179,310);
    
    this->comboFrame->addChild(comboBar);
    
    this->t = -2;
    
    this->scheduleUpdate();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto listenerKeyPad = EventListenerKeyboard::create();
    listenerKeyPad->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
    listenerKeyPad->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyPad, this);
    
    
    this->rate = Sprite::create();
    this->rate->setPosition(960, 450);
    this->addChild(this->rate);
    
    
    return true;
}

GameLayer* GameLayer::createWithId(int id,const char* diff, int pkMode)
{
    auto gamelayer = GameLayer::create();
    gamelayer->mode = pkMode;
    gamelayer->songId = id;
    strcpy(gamelayer->diff, diff);
    strcpy(gamelayer->songName, SongsInfo::getInstance()->getInfoById(id)->name);
    gamelayer->loadFile();
    gamelayer->showTitle();
    if(pkMode)
    {
        gamelayer->initPKMode();
    }
	gamelayer->setPauseButton(pkMode);
    return gamelayer;
}
void GameLayer::initPKMode()
{
    for(int i=0;i<8;i++)
    {
        this->itemOn[i] = false;
    }

    this->scoreLabel_OP = Label::createWithSystemFont("0000000", "Arial", 80);
    
    this->scoreLabel_OP->setPosition(0,1080);
    
    this->scoreLabel_OP->setAnchorPoint(Vec2(0,1));
    
    this->addChild(this->scoreLabel_OP);
    
    SocketIOClient::getInstance()->listen("sendScore", [=](SIOClient* client, std::string msg){
        rapidjson::Document doc;
        doc.Parse<0>(msg.c_str());
        
        char score[32];
        
        sprintf(score, "%07d",doc["score"].GetInt());
        
        this->scoreLabel_OP->setString(score);
    });
    
    this->schedule(schedule_selector(GameLayer::updateScore),0.2f);
    
}

void GameLayer::updateScore(float dt)
{
    char msg[128];
    sprintf(msg, "{\"score\":%d,\"combo\":%d}",this->score,this->combo);
    SocketIOClient::getInstance()->send("updateScore",msg);
}

void GameLayer::update(float dt)
{
    this->t+=dt;
    
    if (this->t > this->offset&&this->t-dt <= this->offset)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(filename,false);
    }
    
    while(!this->notes.empty()&&this->notes.at(0)->t < this->t*1000)
    {
        this->dropTag(this->notes.at(0)->x);
    }
    
    if(this->notes.empty())
    {
        bool empty = true;
        for(int i=0;i<4;i++)
        {
            if(!tags[i].empty())empty = false;
        }
        if(empty)
        {
            this->unscheduleUpdate();
            this->board->runAction(Sequence::create(DelayTime::create(2),CallFunc::create([=](){
                this->complete();
            }),NULL));
        }
    }
}

void GameLayer::loadFile()
{
    sprintf(filename, "songs/%d/%s.mp3",songId,songName);
    
    char osuFilename[128];
    
    sprintf(osuFilename, "songs/%d/%s[%s].osu",songId,songName,diff);
    
    std::string str = FileUtils::getInstance()->getStringFromFile(osuFilename);
    
    std::string line;
    
    bool isHitObject = false;
    
    while(str.find("\n")!=string::npos)
    {
        size_t n = str.find("\n");
        
        line = str.substr(0,n-1);
        
        str = str.erase(0,n+1);
        
        if(isHitObject)
        {
            n = line.find(",");
            string number = line.substr(0,n);
            line = line.erase(0,n+1);
            int data1 = atoi(number.c_str());
            
            n = line.find(",");
            number = line.substr(0,n);
            line = line.erase(0,n+1);
            //int data2 = atoi(number.c_str());
            
            n = line.find(",");
            number = line.substr(0,n);
            line = line.erase(0,n+1);
            int data3 = atoi(number.c_str());
            
            n = line.find(",");
            number = line.substr(0,n);
            line = line.erase(0,n+1);
            int data4 = atoi(number.c_str());
            
            n = line.find(",");
            number = line.substr(0,n);
            line = line.erase(0,n+1);
            //int data5 = atoi(number.c_str());
            
            n = line.find(":");
            number = line.substr(0,n);
            line = line.erase(0,n+1);
            int data6 = atoi(number.c_str());
            
            if(data1<=120)data1 = 0;
            if(data1>120&&data1<=240)data1 = 1;
            if(data1>240&&data1<=360)data1 = 2;
            if(data1>360&&data1<=480)data1 = 3;
            
            if(data4!=128)
                this->notes.pushBack(SimpleNote::createSimpleNote(data1, data3, data4, data3));
            if(data4==128)
                this->notes.pushBack(LongNote::createLongNote(data1, data3, data4, data6));
        }
        if(line=="[HitObjects]")
        {
            isHitObject = true;
        }
    }
    
}

bool GameLayer::onTouchBegan(Touch *touch, Event *pEvent)
{
    auto p = this->convertTouchToNodeSpace(touch);
    
    for(int i=0;i<4;i++)
    {
        if(p.x>i*1920/4&&p.x<(i+1)*1920/4&&p.y<500)
        {
            this->click(i);
            break;
        }
    }
    
    return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *pEvent)
{
    auto p = this->convertTouchToNodeSpace(touch);
    
    for(int i=0;i<4;i++)
    {
        if(p.x>i*1920/4&&p.x<(i+1)*1920/4&&p.y<500)
        {
            break;
        }
    }
}

void GameLayer::onTouchEnded(Touch *touch, Event *pEvent)
{
    auto p = this->convertTouchToNodeSpace(touch);
    
    for(int i=0;i<4;i++)
    {
        if(p.x>i*1920/4&&p.x<(i+1)*1920/4&&p.y<500)
        {
            this->release(i);
            break;
        }
    }
}
void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_D)this->click(0);
    if(keyCode == EventKeyboard::KeyCode::KEY_F)this->click(1);
    if(keyCode == EventKeyboard::KeyCode::KEY_J)this->click(2);
    if(keyCode == EventKeyboard::KeyCode::KEY_K)this->click(3);
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_D)this->release(0);
    if(keyCode == EventKeyboard::KeyCode::KEY_F)this->release(1);
    if(keyCode == EventKeyboard::KeyCode::KEY_J)this->release(2);
    if(keyCode == EventKeyboard::KeyCode::KEY_K)this->release(3);
}


void GameLayer::dropTag(int col)
{
    Note* tag = this->notes.at(0);
    
    tag->display();
    
    tag->setPosition(key1Pos+Vec2(keyDis*col,3000));
    
    this->board->addChild(tag);
    
    this->tags[col].pushBack(tag);
    
    this->notes.erase(0);
}

void GameLayer::click(int col)
{
    this->pressLight[col]->stopAllActions();
    this->pressLight[col]->setOpacity(255);
    
    if(this->tags[col].size()==0)return;
    
    Note* tag = this->tags[col].at(0);
    
    if (abs((this->t - this->offset) * 1000 - tag->t) > RATE_STD[3]) return;
    else if (abs((this->t - this->offset) * 1000 - tag->t) > RATE_STD[2]) this->getRate(3);
    else if (abs((this->t - this->offset) * 1000 - tag->t) > RATE_STD[1]) this->getRate(2);
    else if (abs((this->t - this->offset) * 1000 - tag->t) > RATE_STD[0]) this->getRate(1);
    
    tag->click();
    
}

void GameLayer::release(int col)
{
    this->pressLight[col]->stopAllActions();
    this->pressLight[col]->runAction(FadeTo::create(0.3f, 0));
    
    if(this->tags[col].size()==0)return;
    this->tags[col].at(0)->release();
}

void GameLayer::miss(int col)
{
    this->getRate(0);
}

void GameLayer::getRate(int rate)
{
    if(rate==0&&itemOn[0]&&itemCount[0]>0)
    {
        itemCount[0]--;
        getRate(3);
        return;
    }
    if(rate==3&&itemOn[1]&&itemCount[1]>0)
    {
        itemCount[1]--;
        getRate(2);
        return;
    }
    
    char str[20];
    
    sprintf(str, "img/game/rate%d.png",rate);
    
    this->rate->setTexture(str);
    
    this->rate->setOpacity(255);
    this->rate->setScale(2);
    this->rate->stopAllActions();
    this->rate->runAction(Sequence::create(ScaleTo::create(0.1, 1.8),DelayTime::create(0.5f),FadeTo::create(0.3f,0 ),NULL));
    
    this->rateCount[rate]++;
    
    this->score+=RATE_SCORE[rate];
    
    sprintf(str, "%07d",score);
    
    this->scoreLabel->setString(str);
    
    if(rate!=0)this->comboIncrese();
    else
        this->comboClear();
    
    this->updateHp(RATE_HP[rate]);
}
void GameLayer::playAnimate(int col, int type)
{
    Animation* ani;
    Animate* act;
    if(type==0)
    {
        ani = AnimationCache::getInstance()->getAnimation("hit");
        act = Animate::create(ani);
    }
    else if(type==1)
    {
        ani = AnimationCache::getInstance()->getAnimation("lhit");
        ani->setLoops(999);
        act = Animate::create(ani);
    }
    hitEffect[col]->stopAllActions();
    
    hitEffect[col]->runAction(act);
}
void GameLayer::comboIncrese()
{
    this->combo++;
    if(this->combo>this->maxCombo)this->maxCombo = this->combo;
    
    char str[20];
    sprintf(str, "%d",this->combo);
    this->comboLabel->setPositionX(960-strlen(str)*184/2);
    this->comboLabel->setString(str);
    this->comboLabel->setPositionY(680);
    this->comboLabel->stopAllActions();
    this->comboLabel->runAction(MoveBy::create(0.2f, Vec2(0,20)));
    
    this->comboBar->setPercentage(combo*100.0f/MAX_POWER);
}
void GameLayer::comboClear()
{
    this->comboLabel->setString("");
    this->combo=0;
    this->comboBar->setPercentage(combo*100.0f/MAX_POWER);
}
void GameLayer::complete()
{
    auto shadow = LayerColor::create(Color4B(0,0,0,255));
    shadow->setOpacity(0);
    shadow->runAction(Sequence::create(FadeTo::create(0.5f, 255),DelayTime::create(0.4f),CallFunc::create([=](){
        auto overLayer = GameOver::create();
        overLayer->setData(songId,songName, diff,3, score, maxCombo, 100,rateCount[0],rateCount[3],rateCount[2],rateCount[1]);
        this->getParent()->addChild(overLayer);
		Director::sharedDirector()->resume();
        this->removeFromParent();
    }),FadeTo::create(0.5f, 255),CallFunc::create([=](){
        shadow->removeFromParent();
    }), NULL));
    this->getParent()->addChild(shadow,9);
    
    char str[256];
    sprintf(str, "{\"songId\":%d,\"diffName\":\"%s\",\"score\":%d,\"grade\":%d,\"combo\":%d,\"missCount\":%d,\"poorCount\":%d,\"goodCount\":%d,\"coolCount\":%d,\"acc\":%d}",songId,diff,score,3,maxCombo,rateCount[0],rateCount[3],rateCount[2],rateCount[1],100);
    SocketIOClient::getInstance()->send("uploadScore", str);
}
void GameLayer::updateHp(int delta)
{
    this->hp+=delta;
    
    if(this->hp<0){
        this->hp = 0;
    }
    if(this->hp>MAX_HP)
    {
        this->hp = MAX_HP;
    }
    
    this->hpBar->setPercentage(hp*100.0f/MAX_HP);
}
void GameLayer::showTitle()
{
    auto name = Label::createWithSystemFont(this->songName,"",200);
    
    name->setPosition(810,740);
    
    name->setOpacity(0);
    
    name->runAction(MoveBy::create(2.0f, Vec2(300,0)));
                    
    name->runAction(Sequence::create(FadeTo::create(1.0f, 255),FadeTo::create(1.0f, 0),NULL));
    
    this->addChild(name);
    
    auto diff = Label::createWithSystemFont(this->diff, "", 128);
    
    diff->setPosition(1110,500);
    
    diff->setOpacity(0);
    
    diff->runAction(MoveBy::create(2.0f, Vec2(-300,0)));
    
    diff->runAction(Sequence::create(FadeTo::create(1.0f, 255),FadeTo::create(1.0f, 0),NULL));
    
    this->addChild(diff);
}


void GameLayer::gamePause()
{
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	Director::sharedDirector()->pause();

	pauseLayer = PauseLayer::createWithSong(this->songId,this->diff,0);

	this->addChild(pauseLayer);
}

void GameLayer::setPauseButton(int pkMode)
{
	if (!pkMode)
	{
		btn_pause = MenuItemImage::create("img/game/btn_pause.png", "img/game/btn_pause_p.png", CC_CALLBACK_0(GameLayer::gamePause, this));

		btn_pause->setPosition(Vec2(btn_pause->getContentSize().width / 2, 980));


		auto ring = Sprite::create("img/selectsongs/ring.png");

		ring->setPosition(130, 100);

		ring->runAction(RepeatForever::create(RotateBy::create(4, 360)));

		btn_pause->addChild(ring);


		Menu* menu = Menu::create(btn_pause, NULL);

		menu->setPosition(Point::ZERO);

		this->addChild(menu);
	}
}