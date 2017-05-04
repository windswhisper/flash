#include "ShopItemInfo.h"

bool ShopItemInfo::init()
{
	btn_buyShopItem = MenuItemImage::create("img/shop/btn_buy.png", "img/shop/btn_buy_p.png");

	btn_buyShopItem->setPosition(Vec2(0, -300));

    Menu* menu = Menu::create(btn_buyShopItem,NULL);
    
    menu->setPosition(Vec2::ZERO);
    
	this->addChild(menu);

	return true;
}

void ShopItemInfo::buyShopItem()
{

}

ShopItemInfo* ShopItemInfo::createWithInfo(char* ShopItemID,char* ShopItemIntro,int price,ccMenuCallback callFunc)
{
	ShopItemInfo* shopItemInfo = ShopItemInfo::create();

	shopItemInfo->shopItemID = ShopItemID;

    shopItemInfo->shopItemIntro = ShopItemIntro;

    shopItemInfo->price = price;

    shopItemInfo->btn_buyShopItem->initWithCallback(callFunc);

	shopItemInfo->setShopItemID();

	return shopItemInfo;
}

void ShopItemInfo::setShopItemID()
{
	shopItemIdText = Text::create(shopItemID, "", 72);

    shopItemIdText->ignoreContentAdaptWithSize(false);
    
    shopItemIdText->setTextColor(Color4B(228,193,68,255));
    
	shopItemIdText->setPosition(Vec2(0, 400));

	this->addChild(shopItemIdText);
    
    shopItemIntroText = Text::create(shopItemIntro, "", 48);
    
    shopItemIntroText->setAnchorPoint(Vec2(0.5,1));
    
    shopItemIntroText->setTextAreaSize(Size(520,800));
    
    shopItemIntroText->ignoreContentAdaptWithSize(false);
    
    shopItemIntroText->setPosition(Vec2(20, 300));
    
    this->addChild(shopItemIntroText);
    
    char str[32];
    
    sprintf(str, "%dG" ,price);
    
    priceText = Text::create(str, "", 72);
   
    priceText->setPosition(Vec2(0, -300));
    
    this->addChild(priceText);

}
