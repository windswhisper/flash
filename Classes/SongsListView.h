#ifndef __SONGS_LIST_VIEW_H__
#define __SONGS_LIST_VIEW_H__

#include "cocos2d.h"

USING_NS_CC;


class SongsListView : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(SongsListView);
    
    bool onTouchBegan(Touch *touch,Event *pEvent);
    
    void onTouchMoved(Touch *touch,Event *pEvent);
    
    void onTouchEnded(Touch *touch,Event *pEvent);
    
    void update(float dt);
    
    void addOption(const char* name);
    
    void touchItem(Sprite* item);
    
    void canelTouch();
    
    void selectItem(int i);
    
    void showDiffList(int i);
    
    Vector<Sprite*> itemSong;
    
    Node* root;
    
    float height;
    
    float option_height;
    
    float visible_height;
    
    float scoll_speed;
    
    float max_speed;
    
    float last_y;
    
    float now_y;
    
    bool isMoving;
    
    Sprite* itemOnPress;
    
    bool isPause;
    
};

#endif
