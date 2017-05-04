#ifndef __SHOP_CONFIG_H__
#define __SHOP_CONFIG_H__

#include "cocos2d.h"

USING_NS_CC;

struct ItemInfo
{
    char name[32];
    char intro[256];
    int price;
};

class ShopConfig
{
public:
    static ShopConfig* getInstance();
    
    void load();
    
    ItemInfo getInfo(char* id);
    
    static bool checkCoin(int price);
    
    rapidjson::Document doc;
    
};
static ShopConfig* _shopConfig;

#endif
