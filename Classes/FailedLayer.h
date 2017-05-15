#ifndef __FAILED_LAYER_H__
#define __FAILED_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class FailedLayer : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(FailedLayer);

	void playAgain();

	void back();

	static FailedLayer* createWithSong(int id, char* name, char* diff, int pkMode);

private:

	MenuItemImage* btn_playAgain;

	MenuItemImage* btn_back;

	Sprite* failedLabel;

	Sprite* pauseBg;

	int songId;

	char songdiff[32];

	int pkMode;
    
    char name[64];
};

#endif
