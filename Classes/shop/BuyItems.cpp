#include "BuyItems.h"
#include "ShopConfig.h"
#include "UserInfo.h"

bool BuyItems::init()
{
	scrollView = ScrollView::create();

	scrollView->setContentSize(Size(1350,600));

	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	
	scrollView->setBounceEnabled(true);

	scrollView->setInnerContainerSize(scrollView->getContentSize());

	scrollView->setPosition(Vec2(300,400));

	this->addChild(scrollView);
    
    itemInfo = nullptr;
    
    auto bg = Sprite::create("img/shop/songspackage/songspackageinfobg.png");
    
    bg->setPosition(1930,733);
    
    this->addChild(bg);
    
	this->setItem();

	return true;
}

void BuyItems::setItem()
{
	Layout* item = Layout::create();

	item->setContentSize(Size(400,400));

	item->setPosition(Vec2(0,0));

	for (int i = 0; i < 6; ++i)
    {
        
		sprintf(itemIdArray[i],"item%d",i + 1);

		items[i] = Button::create("img/shop/songspackage/item.png","img/shop/songspackage/item_p.png");

		items[i]->setContentSize(Size(100,100));

		items[i]->setPosition(Vec2(300 + 400 * (i % 3),450 - 300 * (i / 3)));

		items[i]->addTouchEventListener(CC_CALLBACK_0(BuyItems::selectItem, this, i));

		item->addChild(items[i]);

		char itemIconName[100];

		sprintf(itemIconName, "img/selectsongs/itemIcon/itemIcon%d.png", i%3+1);

		auto itemIcon = Sprite::create(itemIconName);

		itemIcon->setScale(0.3);

		itemIcon->setPosition(Vec2(items[i]->getContentSize().width / 2, items[i]->getContentSize().height / 2));

		items[i]->addChild(itemIcon);
	}

	scrollView->addChild(item);

}

void BuyItems::selectItem(int i)
{
    if(itemInfo!=nullptr)
        this->removeChild(itemInfo);

    ItemInfo info = ShopConfig::getInstance()->getInfo(itemIdArray[i]);
    
    itemInfo = ShopItemInfo::createWithInfo(info.name,info.intro,info.price,CC_CALLBACK_0(BuyItems::buyItem, this,i));

	itemInfo->setPosition(1930,733);

	this->addChild(itemInfo);
}

void BuyItems::buyItem(int i)
{
    switch (i) {
        case 0:
            if(ShopConfig::checkCoin(10))
            {
                UserInfo::getInstance()->item[0]++;
            }
            else{
                 printf("buyfail");
            }
            break;
            
        default:
            break;
    }
}
