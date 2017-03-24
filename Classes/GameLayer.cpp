#include "GameLayer.h"
#include  <iostream>
#include  <fstream>
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;


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
    _gamelayer->hitEffect[this->x]->stopAllActions();
    _gamelayer->hitEffect[this->x]->setSpriteFrame("space.png");
}


bool GameLayer::init()
{
    _gamelayer = this;
    
	this->speed = 1.5;
	this->offset = 2 / speed;
	this->musicFileName = "1.mp3";

    this->key1Pos = Vec2(229,350);
    this->keyDis = 318;
    
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(this->musicFileName);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/game/hit.plist");
    AnimationCache::getInstance()->addAnimationsWithFile("img/game/hit_ani.plist");
    AnimationCache::getInstance()->addAnimationsWithFile("img/game/lhit_ani.plist");
    
    root = Node::create();
    
    this->addChild(root);
    
    board = Sprite::create("img/game/board.png");
    
    board->setRotation3D(Vec3(-40,0,0));
    
    board->setScale(0.25);
    
    board->setPosition(0,250);
    
    root->addChild(board);
    
    root->setPosition(960,540);
    
    root->setScale(2);
    
   
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
    
    //this->schedule(schedule_selector(GameLayer::droper), 0.5f);

    this->t = 0;
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
    
    this->loadFile();
    
	this->rate = Label::create("","",128);
	this->rate->setPosition(960, 540);
	this->addChild(this->rate);

    
    return true;
}

void GameLayer::update(float dt)
{
    this->t+=dt;

	if (this->t > this->offset&&this->t-dt <= this->offset)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(this->musicFileName,false);
	}
    
    while(!this->notes.empty()&&this->notes.at(0)->t < this->t*1000)
    {
        this->dropTag(this->notes.at(0)->x);
        
    }
}

void GameLayer::loadFile()
{
    std::string str = FileUtils::getInstance()->getStringFromFile("1.osu");
    
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
            
            if(data1==64)data1 = 0;
            if(data1==192)data1 = 1;
            if(data1==320)data1 = 2;
            if(data1==448)data1 = 3;
            
            if(data4==1)
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
        if(p.x>i*1920/4&&p.x<(i+1)*1920/4&&p.y<300)
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
        if(p.x>i*1920/4&&p.x<(i+1)*1920/4&&p.y<300)
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
        if(p.x>i*1920/4&&p.x<(i+1)*1920/4&&p.y<300)
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
    
    if (abs((this->t - this->offset) * 1000 - tag->t) > 200) return;
	else if (abs((this->t - this->offset) * 1000 - tag->t) > 150) this->getRate(3);
	else if (abs((this->t - this->offset) * 1000 - tag->t) > 60) this->getRate(2);
	else if (abs((this->t - this->offset) * 1000 - tag->t) > 0) this->getRate(1);
    
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
    if(rate==0)
        this->rate->setString("Miss");
    if(rate==1)
        this->rate->setString("Perfect");
    if(rate==2)
        this->rate->setString("Great");
    if(rate==3)
        this->rate->setString("Good");
    
    this->rate->setScale(1.2);
    this->rate->stopAllActions();
    this->rate->runAction(ScaleTo::create(0.1, 1));
    
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

