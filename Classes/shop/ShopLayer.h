#ifndef __SHOP_LAYER_H__
#define __SHOP_LAYER_H__

#include "cocos2d.h"
#include "SongsExtraction.h"
#include "SongsPackage.h"
#include "BuySkill.h"
#include "BuyItems.h"

USING_NS_CC;

class ShopLayer : public Layer
{
    ShopLayer();
    ~ShopLayer();
public:
	virtual bool init();

	CREATE_FUNC(ShopLayer);

    static ShopLayer* getInstance();
    
	void backToMenu();

	void close();

	Sprite* addPressSprite();

	void songsSelect();

	void songsPackageSelect();

	void skillSelect();

	void itemSelect();

	void duelSelect();

	void skinSelect();

    void updateMoney();
    
	MenuItemImage* btn_mainmenu;

	MenuItemImage* btn_skin;

	MenuItemImage* btn_duel;

	MenuItemImage* btn_item;

	MenuItemImage* btn_skill;

	MenuItemImage* btn_songspackage;

	MenuItemImage* btn_songsextraction;

	MenuItemImage* button;

	Sprite* shop_bg;

	Sprite* tabSelect;

	Node* node;

	SongsExtraction* songsExtraction;

	SongsPackage* songsPackage;

	BuySkill* skill;
    
    BuyItems* buyItems;
    
    Label* moneyLabel;
};
static ShopLayer* _shopLayer;
#endif
