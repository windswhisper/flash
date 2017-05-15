#ifndef __SONGS_EXTRACTION_H__
#define __SONGS_EXTRACTION_H__

#include "cocos2d.h"
#include <random>
<<<<<<< HEAD
#include "ui\CocosGUI.h"
#include <vector>
=======
#include "ui/CocosGUI.h"
>>>>>>> 682e650d263c65e4df1a383a042ed0f929b1fdc8

USING_NS_CC;
using namespace ui;
//using namespace std;

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

	Vector<Sprite*> songsCover;

//	Vector<char*> songsCoverPath;

	int count;
};

#endif
