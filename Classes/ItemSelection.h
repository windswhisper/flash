#ifndef __SELECTION_ITEM_H__
#define __SELECTION_ITEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class ItemSelection : public Node
{
public:
	bool init();

	CREATE_FUNC(ItemSelection);

	void changeItem();

	void selectItem(Ref* pSender, Widget::TouchEventType type, Button* items_btn,int i);

	void setItem();

private:
	Sprite* itemSelectionbg;

	Sprite* itemSelectionSwitch;

	MenuItemImage* changeItem_button;

	bool isDown;

	int isSelect[20];

    Vector<Sprite*> itemButtonSelect;

	Node* node;

	Button* items[20];

//	Sprite* btn_sel;

//	Sprite* itemSel;

};
#endif