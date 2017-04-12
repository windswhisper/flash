#ifndef __SHOP_ITEM_INFO_H__
#define __SHOP_ITEM_INFO_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class ShopItemInfo : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(ShopItemInfo);

	void buyShopItem();

	static ShopItemInfo* createWithInfo(char* shopItemID);

	void setShopItemID();

	Sprite* bg;

	Button* btn_buyShopItem;

	char* shopItemID;

	Text* shopItemIdText;
};

#endif