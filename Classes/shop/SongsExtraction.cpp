#include "SongsExtraction.h"


bool SongsExtraction::init()
{
	songsExtractionFrame = Sprite::create("img/shop/songsextraction/songsextraction_frame.png");

	songsExtractionFrame->setPosition(1000, 530);

	this->addChild(songsExtractionFrame);


	songsExtractionBg = Sprite::create("img/shop/songsextraction/songsextraction_bg.png");

	songsExtractionBg->setPosition(songsExtractionFrame->getContentSize().width/2,songsExtractionFrame->getContentSize().height/2);

	songsExtractionFrame->addChild(songsExtractionBg);

	
	btn_extractForOne = MenuItemImage::create("img/shop/btn_buy.png", "img/shop/btn_buy_p.png", CC_CALLBACK_0(SongsExtraction::extractForOne,this));

	btn_extractForOne->setPosition(700,130);

	auto extractionForOne = Sprite::create("img/shop/songsextraction/extractionForOne.png");

	extractionForOne->setPosition(btn_extractForOne->getContentSize().width / 2, btn_extractForOne->getContentSize().height/2);

	btn_extractForOne->addChild(extractionForOne);

	btn_extractForTen = MenuItemImage::create("img/shop/btn_buy.png", "img/shop/btn_buy_p.png", CC_CALLBACK_0(SongsExtraction::extractForTen, this));

	btn_extractForTen->setPosition(1300,130);

	auto extractionForTen = Sprite::create("img/shop/songsextraction/extractionForTen.png");

	extractionForTen->setPosition(btn_extractForTen->getContentSize().width / 2, btn_extractForTen->getContentSize().height / 2);

	btn_extractForTen->addChild(extractionForTen);


	Menu* menu = Menu::create(btn_extractForOne, btn_extractForTen,NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	return true;
}

void SongsExtraction::extractForOne()
{
	auto node = Node::create();
	auto bg = Sprite::create("img/shop/shop_bg.png");
	node->addChild(bg);
	char coverName[64];
	srand((unsigned int)time(0));
	int num = random(1,10);
	sprintf(coverName,"songs/%d/cover.jpg",num);
//	songsExtractionBg->setTexture(coverName);
	auto coverBg = Sprite::create(coverName);
	coverBg->setPosition(Vec2(bg->getContentSize().width/2,bg->getContentSize().height/2));
	bg->addChild(coverBg);
	auto label = Label::create("ifsafjsfjeifjas","",72);
	label->setPosition(Vec2(960,900));
	bg->addChild(label);
	node->setPosition(Vec2(760, 570));
	this->addChild(node,10);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			coverBg->setOpacity(180);
			return true;
		}
		return false;
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->removeAllChildren();
		target->removeFromParent();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bg);
}

void SongsExtraction::extractForTen()
{

}

