#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(PauseLayer);

	void continuePlay();

	void playAgain();

	void back();

	static PauseLayer* createWithSong(int id,char* name, char* diff, int pkMode);

private:
	MenuItemImage* btn_continue;

	MenuItemImage* btn_playAgain;

	MenuItemImage* btn_back;

	Sprite* pauseBg;

	int songId;

	char songdiff[32];

	int pkMode;
    
    char name[64];
};

#endif
