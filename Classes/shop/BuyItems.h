#ifndef __BUY_ITEMS_H__
#define __BUY_ITEMS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ShopItemInfo.h"

USING_NS_CC;
using namespace ui;

class BuyItems : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(BuyItems);

	void selectItem(int i);

	void setItem();

    void buyItem(int i);
    
	ScrollView* scrollView;

	Button* items[20];

	ShopItemInfo* itemInfo;
    
    char itemIdArray[20][64];
};

#endif
