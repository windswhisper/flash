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
    
    void changerCover(const char* fileName);
    
    MenuItemImage* btn_mainmenu;
    
    MenuItemImage* btn_setting;
    
    Node* songsList;
    
    Node* coverScreen;
    
    Sprite* songCover;
};

#endif
