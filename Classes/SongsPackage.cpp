#include "SongsPackage.h"

bool SongsPackage::init()
{
	scrollView = ScrollView::create();

	scrollView->setContentSize(Size(1250,600));

	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	
	scrollView->setBounceEnabled(true);

	scrollView->setInnerContainerSize(scrollView->getContentSize());

	scrollView->setPosition(Vec2(300,400));

	this->addChild(scrollView);

	this->setSongspackage();

	return true;
}

void SongsPackage::setSongspackage()
{
	Layout* item = Layout::create();

	item->setContentSize(Size(400,400));

	item->setPosition(Vec2(0,0));

	for (int i = 0; i < 8; ++i)
	{
		songsPackage[i] = Button::create("img/shop/songspackage/item.png","img/shop/songspackage/item_p.png");

		songsPackage[i]->setContentSize(Size(100,100));

		songsPackage[i]->setPosition(Vec2(200 + 300 * (i % 4),450 - 300 * (i / 4)));

		songsPackage[i]->addTouchEventListener(CC_CALLBACK_0(SongsPackage::itemSelect, this));

		item->addChild(songsPackage[i]);
	}

	scrollView->addChild(item);

	//songsPackage1 = MenuItemImage::create("img/shop/songspackage/item.png", "img/shop/songspackage/item_p.png", CC_CALLBACK_0(SongsPackage::itemSelect, this));
	//songsPackage1->setContentSize(Size(200,200));
	//songsPackage1->setPosition(100, 100);
	///*songsPackage2 = MenuItemImage::create("img/shop/songspackage/item.png", "img/shop/songspackage/item_p.png", CC_CALLBACK_0(SongsPackage::itemSelect, this));

	//songsPackage2->setPosition(400, 500);
	//songsPackage3 = MenuItemImage::create("img/shop/songspackage/item.png", "img/shop/songspackage/item_p.png", CC_CALLBACK_0(SongsPackage::itemSelect, this));

	//songsPackage3->setPosition(400, 600);
	//*/
	//Layout* item = Layout::create();

	//item->setContentSize(songsPackage1->getContentSize());

	//songsPackage1->setPosition(Vec2(item->getContentSize().width / 2, item->getContentSize().height / 2));
	////	songsPackage2->setPosition(Vec2(item->getContentSize().width / 2, item->getContentSize().height / 2));
	//item->addChild(songsPackage1);
	////item->addChild(songsPackage2);
	////item->addChild(songsPackage3);




	//scrollView->addChild(item);
}

void SongsPackage::itemSelect()
{

}