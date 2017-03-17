#include "SongsListView.h"

#include "SongsInfo.h"

bool SongsListView::init()
{
    this->scoll_speed = 0;
    this->max_speed = 80;
    this->height = 160*5;
    this->option_height = 160;
    this->visible_height = 800;
    
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
    
    for(int i=0;i<songs.size()+10;i++)
    {
        char str[50];
        sprintf(str, "Flower Dance%d", i);
        this->addOption(str);
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
    this->scoll_speed = 0;
    
    this->isMoving = false;
    
    return true;
}
void SongsListView::onTouchMoved(Touch *touch,Event *pEvent)
{
    this->isMoving = true;
    
    this->root->setPositionY(this->root->getPositionY()+ touch->getLocation().y-touch->getPreviousLocation().y);
}
void SongsListView::onTouchEnded(Touch *touch,Event *pEvent)
{
    Point p = this->convertTouchToNodeSpace(touch);
    
    if(!this->isMoving)
    {
        for(auto v : this->itemSong)
        {
            if(v->getBoundingBox().containsPoint(p)&&v->getOpacity()!=0)
            {
                //auto scene = StageMapScene::create_map(this->itemSong.getIndex(v));
                
               // Director::getInstance()->pushScene(TransitionSlideInR::create(0.2f, scene));
            }
        }
    }
    else if(abs(now_y - last_y)>0.2f);
    {
        this->scoll_speed = (now_y - last_y)*3;
    }
}
