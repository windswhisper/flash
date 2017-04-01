#include "ItemSelection.h"

//#include "SongsLayer.h"

bool ItemSelection::init()
{
	isDown = false;

//	isSelect[20] = {1};

	this->itemSelectionbg = Sprite::create("img/selectsongs/ItemSelection_bg.png");

	this->setAnchorPoint(Point::ZERO);

	this->addChild(itemSelectionbg);

	changeItem_button = MenuItemImage::create("img/selectsongs/switch_frame.png", "img/selectsongs/switch_frame.png", CC_CALLBACK_0(ItemSelection::changeItem, this));

	changeItem_button->setPosition(-390, -35);

	itemSelectionSwitch = Sprite::create("img/selectsongs/switch.png");

	itemSelectionSwitch->setPosition(55, 150);

	changeItem_button->addChild(itemSelectionSwitch);

	Menu* menu = Menu::create(changeItem_button, NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	this->setItem();

	return true;
}



void ItemSelection::setItem()
{
/*
	auto item1 = Sprite::create("img/selectsongs/ItemSelection_item.png");

	item1->setPosition(-244,-35);

	auto item2 = Sprite::create("img/selectsongs/ItemSelection_item.png");

	item2->setPosition(-46, -35);

	auto item3 = Sprite::create("img/selectsongs/ItemSelection_item.png");

	item3->setPosition(152, -35);

	auto item4 = Sprite::create("img/selectsongs/ItemSelection_item.png");

	item4->setPosition(350, -35);
*/
	Layout* item = Layout::create();

	item->setSize(Size(900,200));

	item->setPosition(Vec2(-350,-130));

	item->setClippingEnabled(true);

	node = Node::create();

	for (int i = 0; i < 8; ++i)
	{
		isSelect[i] = 0;

		items[i] = Button::create("img/selectsongs/items.png");

		items[i]->setPosition(Vec2(-224 + 198 * (i % 4), -35 - 200 * (i / 4)));

		items[i]->addTouchEventListener(CC_CALLBACK_2(ItemSelection::selectItem,this, items[i],i));

		node->addChild(items[i]);
	}
/*
	node->addChild(item1);

	node->addChild(item2);

	node->addChild(item3);

	node->addChild(item4);
*/
	node->setPosition(Vec2(330, 130));

	item->addChild(node);

	this->addChild(item);

}

void ItemSelection::changeItem()
{
	if (!isDown)
	{
		auto action = MoveBy::create(0.3f, Vec2(0, -95));

		this->itemSelectionSwitch->runAction(action);

		node->runAction(EaseSineOut::create(MoveBy::create(0.3f, Vec2(0, 200))));

		isDown = true;
	}
	else
	{
		this->itemSelectionSwitch->runAction(MoveBy::create(0.3f,Vec2(0,95)));

		node->runAction(EaseSineOut::create(MoveBy::create(0.3f, Vec2(0, -200))));

		isDown = false;
	}
}

void ItemSelection::selectItem(Ref* pSender, Widget::TouchEventType type,  Button* items_btn,int i)
{
	if ( type == Widget::TouchEventType::BEGAN)
	{
		if (isSelect[i] == 0)
		{
			btn_sel = Sprite::create("img/selectsongs/items_p.png");

			itemSel = Sprite::create("img/selectsongs/items_s.png");

			btn_sel->setPosition(95, 90);

			itemSel->setPosition(150, 40);

			btn_sel->addChild(itemSel);

			items_btn->addChild(btn_sel);

			isSelect[i] = 1;

		}
		else
		{
			items_btn->removeAllChildren();

			isSelect[i] = 0;
		}
	}
}