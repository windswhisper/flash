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

}

void SongsExtraction::extractForTen()
{

}