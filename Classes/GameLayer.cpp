#include "GameLayer.h"
#include  <iostream>
#include  <fstream>
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

bool Note::init()
{
    return true;
}

Note* Note::createNote(int x, int t, int type, int endt)
{
    Note* note = Note::create();
    
    note->x = x;
    note->t = t;
    note->type = type;
    note->endt = endt;
    
    return note;
}

bool GameLayer::init()
{
    this->board = Node::create();
    this->addChild(board);
    
    this->setScale(2);
    
	this->speed = 1;
	this->offset = 3 / speed;
	this->musicFileName = "2.mp3";

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(this->musicFileName);

    this->setScale(2);
    for(int i=0;i<4;i++)
    {
        this->key[i] = Sprite::create("img/key.png");
        
        this->key[i]->setPosition(70+30*i,20);
        
        this->key[i]->setRotation3D(Vec3(-45, 0, 0));
        
        this->board->addChild(this->key[i]);
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
    
	this->rate = Label::create("","Arial",20);
	this->rate->setPosition(115, 100);
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
    std::string str = FileUtils::getInstance()->getStringFromFile("2.osu");
    
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
            
            this->notes.pushBack(Note::createNote(data1, data3, data4, data6));
            
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
        if(this->key[i]->getBoundingBox().containsPoint(p))
        {
            this->click(i);
            break;
        }
    }
    
    return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *pEvent)
{
}

void GameLayer::onTouchEnded(Touch *touch, Event *pEvent)
{
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_D)this->click(0);
    if(keyCode == EventKeyboard::KeyCode::KEY_F)this->click(1);
    if(keyCode == EventKeyboard::KeyCode::KEY_J)this->click(2);
    if(keyCode == EventKeyboard::KeyCode::KEY_K)this->click(3);
}

void GameLayer::dropTag(int col)
{
	Note* tag = this->notes.at(0);
	
	tag->p = Sprite::create("img/tag.png");
    
	tag->p->setPosition(115,180);
    
	tag->p->runAction(EaseIn::create(MoveTo::create(this->offset, Vec2(70+col*30,20)),3));
    
	tag->p->setScale(0);
    
	tag->p->runAction(EaseIn::create(ScaleTo::create(this->offset, 1),3));
    
	tag->p->setRotation3D(Vec3(-45, 0, 0));
    
    this->board->addChild(tag->p);
    
    this->tags[col].pushBack(tag);
    
	this->notes.erase(0);
}

void GameLayer::click(int col)
{
    if(this->tags[col].size()==0)return;

    auto tag = this->tags[col].at(0);

	if (abs((this->t - this->offset) * 1000 - tag->t) > 150) this->rate->setString("great");
	else if (abs((this->t - this->offset) * 1000 - tag->t) > 60) this->rate->setString("perfect");
	else if (abs((this->t - this->offset) * 1000 - tag->t) > 0) this->rate->setString("Perfect!");

	this->rate->setScale(1.2);
	this->rate->stopAllActions();
	this->rate->runAction(ScaleTo::create(0.1, 1));


	tag->p->stopAllActions();
    
	tag->p->runAction(FadeTo::create(0.5f, 0));
    
	tag->p->runAction(ScaleTo::create(0.5f, 2.0f));

	this->tags[col].eraseObject(tag);

}
