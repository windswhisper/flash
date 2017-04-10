#include "SongsListView.h"

#include "SongsInfo.h"
#include "SongsLayer.h"

bool SongsListView::init()
{
    this->scoll_speed = 0;
    this->max_speed = 80;
    this->height = 160*5;
    this->option_height = 160;
    this->visible_height = 800;
    
    this->isMoving = false;
    this->isPause = false;
	this->itemOnPress = NULL;

    this->root = Node::create();
    this->addChild(root);
        
    this->scheduleUpdate();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = CC_CALLBACK_2(SongsListView::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(SongsListView::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(SongsListView::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    auto songs = SongsInfo::getInstance()->songs;
    
    for(int i=0;i<songs.size();i++)
    {
        this->addOption(songs[i]->name);
    }
    
    return true;
}
void SongsListView::addOption(const char* name)
{
    Sprite* option = Sprite::create("img/selectsongs/btn_song.png");
    
    option->setPosition(0,-this->itemSong.size()*option_height);
    
    this->root->addChild(option);

    auto title = Label::createWithSystemFont(name,"",72);
    
    title->setAnchorPoint(Vec2(0,0.5));
    
    title->setPosition(80,100);
    
    option->addChild(title);
    
    this->itemSong.pushBack(option);
    
    option->setCascadeOpacityEnabled(true);
    
    option->setOpacity(0);
    
    if(this->itemSong.size()*option_height+option_height>height)
    {
        height = this->itemSong.size()*option_height+option_height;
    }
}
void SongsListView::update(float dt)
{
    if(this->isPause)return;
    
    if(scoll_speed>max_speed)scoll_speed = max_speed;
    if(scoll_speed<-max_speed)scoll_speed = -max_speed;
    
    
    this->root->setPositionY(this->root->getPositionY()+scoll_speed);
    
    if(this->root->getPositionY()<0)
    {
        this->scoll_speed = 0;
        this->root->setPositionY(0);
    }
    if(this->root->getPositionY()>height-visible_height)
    {
        this->scoll_speed = 0;
        this->root->setPositionY(height-visible_height);
    }
    
    if(scoll_speed*scoll_speed<3)scoll_speed=0;
    else if(scoll_speed*scoll_speed<50)scoll_speed/=2;
    else if(scoll_speed*scoll_speed<500)scoll_speed/=1.2;
    else scoll_speed/=1.1;
    
    for(int i = 0;i<this->itemSong.size();i++)
    {
        float opacity = this->itemSong.at(i)->getPositionY()+this->root->getPositionY();
        
        float center = visible_height;
        float edge = 50;
        
        if(abs(opacity+center/2)>center/2)
        {
            opacity = abs(opacity+center/2)-center/2;
            
            if(opacity>edge)opacity = edge;
            
            opacity = 255-255*opacity/edge;
        }
        else
        {
            opacity = 255;
        }
        this->itemSong.at(i)->setOpacity(opacity);
    }
    
    last_y = now_y;
    
    now_y = this->root->getPositionY();
    
}
bool SongsListView::onTouchBegan(Touch *touch,Event *pEvent)
{
    if(this->isPause)return false;
    
    Point p = this->root->convertTouchToNodeSpace(touch);
    
    this->scoll_speed = 0;
    
    this->isMoving = false;
    
    for(auto v : this->itemSong)
    {
        if(v->getBoundingBox().containsPoint(p)&&v->getOpacity()!=0)
        {
            this->touchItem(v);
            break;
        }
    }
    
    return true;
}
void SongsListView::onTouchMoved(Touch *touch,Event *pEvent)
{
    this->isMoving = true;
    
    this->canelTouch();
    
    this->root->setPositionY(this->root->getPositionY()+ touch->getLocation().y-touch->getPreviousLocation().y);
}
void SongsListView::onTouchEnded(Touch *touch,Event *pEvent)
{
    Point p = this->root->convertTouchToNodeSpace(touch);
    
    if(!this->isMoving)
    {
        for(auto v : this->itemSong)
        {
            if(v->getBoundingBox().containsPoint(p)&&v->getOpacity()!=0)
            {
                this->selectItem(this->itemSong.getIndex(v));
 
                break;
            }
        }
    }
    else if(abs(now_y - last_y)>0.2f);
    {
        this->scoll_speed = (now_y - last_y)*3;
    }
    
    this->canelTouch();

}
void SongsListView::touchItem(Sprite* item)
{
    this->canelTouch();
    
    this->itemOnPress = item;
    item->setTexture("img/selectsongs/btn_song_p.png");
}
void SongsListView::canelTouch()
{
    if(this->itemOnPress!=NULL)
        this->itemOnPress->setTexture("img/selectsongs/btn_song.png");
}
void SongsListView::selectItem(int i)
{
    this->isPause = true;
    this->selectId = SongsInfo::getInstance()->songs[i]->id;
    auto songsLayer = (SongsLayer*)this->getParent();
    songsLayer->changeCover(SongsInfo::getInstance()->songs[i]->id,SongsInfo::getInstance()->songs[i]->name);

    for(int n=0;n<5;n++)
    {
        if(i-n-1>=0)
            this->itemSong.at(i-n-1)->runAction(FadeTo::create(0.2f,0));
    }
    for(int n=0;n<5;n++)
    {
        if(this->itemSong.size()>=i+n+2)
            this->itemSong.at(i+n+1)->runAction(FadeTo::create(0.2f,0));
    }
    
    this->root->runAction(Sequence::create(DelayTime::create(0.2f),EaseSineOut::create( MoveTo::create((-this->root->getPositionY()-this->itemSong.at(i)->getPositionY())/1200,Vec2(0,-this->itemSong.at(i)->getPositionY()))),CallFunc::create([=]()
    {
        this->showDiffList(i);
    }),NULL));
    
}
void SongsListView::showDiffList(int i)
{
    diffList = Menu::create();
    for(int n=0;n<3;n++)
    {
        MenuItemImage* btn = MenuItemImage::create("img/selectsongs/btn_song.png","img/selectsongs/btn_song_p.png",[=](Ref* pSender){
            auto songsLayer = (SongsLayer*)this->getParent();
            songsLayer->selectSong(SongsInfo::getInstance()->songs[i]->id,SongsInfo::getInstance()->songs[i]->name, "1");
        });
        
        auto title = Label::createWithSystemFont("Easy","",72);
        
        title->setAnchorPoint(Vec2(0,0.5));
        
        title->setPosition(80,100);
        
        btn->addChild(title);
        
        btn->setPosition(0,-n*160);
        
        diffList->addChild(btn);
    }

    diffList->setPosition(0,this->itemSong.at(i)->getPositionY()-option_height);
    this->root->addChild(diffList);
}
void SongsListView::cancelSelect()
{
    for(int n=0;n<5;n++)
    {
        if(this->itemSong.size()>=selectId+n+2)
            this->itemSong.at(selectId+n+1)->runAction(Sequence::create(DelayTime::create(0.5f),FadeTo::create(0.2f,255),NULL));
    }
    
    this->diffList->runAction(FadeTo::create(0.2f,0));

    this->root->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create([=](){
        this->isPause = false;
    }), NULL));
}


