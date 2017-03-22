#ifndef __SONGS_LAYER_H__
#define __SONGS_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class SongsLayer : public Layer
{
public:
    virtual bool init();
    
    CREATE_FUNC(SongsLayer);
    
    void backToMenu();
    
    void setting();
    
    void close(CallFunc* callfunc);
    
    void changeCover(int id);
    
    void selectSong(int id,int diff);
    
    void backToList();
    
    void play();
    
    MenuItemImage* btn_mainmenu;
    
    MenuItemImage* btn_setting;

    Node* songsList;
    
    Node* coverScreen;
    
    Sprite* songCover;
    
    MenuItemImage* playButton;
    
    MenuItemImage* btn_back;
    
    Node* rankList;
    
    Node* itemList;
};

#endif
