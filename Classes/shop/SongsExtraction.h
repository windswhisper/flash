#ifndef __SONGS_EXTRACTION_H__
#define __SONGS_EXTRACTION_H__

#include "cocos2d.h"
#include <random>
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class SongsExtraction : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(SongsExtraction);

	void extractForOne();

	void extractForTen();

	Sprite* songsExtractionBg;

	Sprite* songsExtractionFrame;

	MenuItemImage* btn_extractForOne;

	MenuItemImage* btn_extractForTen;

};

#endif