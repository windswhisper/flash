#ifndef __MAIN_MENU_LAYER_H__
#define __MAIN_MENU_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class MainMenuLayer : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(MainMenuLayer);
    
    void classic();
    
    void duel();
    
    void shop();
    
    void setting();
    
    void close();
    
    Sprite* sp;
    
    MenuItemImage* btnClassic;
    
    MenuItemImage* btnDuel;
    
    MenuItemImage* btnShop;
    
    MenuItemImage* btnSetting;
    
};

#endif
