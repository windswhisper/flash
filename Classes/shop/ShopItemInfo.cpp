#include "ShopItemInfo.h"

bool ShopItemInfo::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();

	bg = Sprite::create("img/shop/songspackage/songspackageinfobg.png");

	bg->setPosition(Vec2(visiblesize.width/2,visiblesize.height/2));

	this->addChild(bg);

	btn_buyShopItem = Button::create("img/shop/btn_buy.png", "img/shop/btn_buy_p.png");

	btn_buyShopItem->setPosition(Vec2(275, 200));

	btn_buyShopItem->addTouchEventListener(CC_CALLBACK_0(ShopItemInfo::buyShopItem, this));

	bg->addChild(btn_buyShopItem);

	return true;
}

void ShopItemInfo::buyShopItem()
{

}

ShopItemInfo* ShopItemInfo::createWithInfo(char* ShopItemID)
{
	ShopItemInfo* shopItemInfo = ShopItemInfo::create();

	shopItemInfo->shopItemID = ShopItemID;

	shopItemInfo->setShopItemID();

	return shopItemInfo;
}

void ShopItemInfo::setShopItemID()
{
	shopItemIdText = Text::create(shopItemID, "Arial", 72);

	shopItemIdText->setPosition(Vec2(250, 850));

	bg->addChild(shopItemIdText);

}
