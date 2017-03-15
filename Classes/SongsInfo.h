#ifndef __SONGS_LAYER_H__
#define __SONGS_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class SongsLayer : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(SongsLayer);
    
    void backToMenu();
    
    void setting();
    
    void close();
    
    MenuItemImage* btn_mainmenu;
    
    MenuItemImage* btn_setting;
    
    
    
};

#endif
