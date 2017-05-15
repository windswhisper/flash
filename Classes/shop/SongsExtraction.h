#ifndef __SONGS_EXTRACTION_H__
#define __SONGS_EXTRACTION_H__

#include "cocos2d.h"
#include <random>
<<<<<<< HEAD
#include "ui\CocosGUI.h"
#include <vector>

=======
#include "ui/CocosGUI.h"
#include <vector>
>>>>>>> 03e8f30d2168dc0dcef8193147c566b991833b9a

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

    void oneSong(int id,const char* name);
    
    void tenSong(std::string msg);
    
	Sprite* songsExtractionBg;

	Sprite* songsExtractionFrame;

	MenuItemImage* btn_extractForOne;

	MenuItemImage* btn_extractForTen;

	Vector<Sprite*> songsCover;

//	Vector<char*> songsCoverPath;

	int count;
};

#endif
