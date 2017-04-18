#ifndef __PK_SELECT_DIFF_H__
#define __PK_SELECT_DIFF_H__

#include "cocos2d.h"
#include "RankingList.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class PKSelectDiff : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(PKSelectDiff);

	void backToMenu();

	void setting();

	void matching();

	void setDiff();

	void lockScreen();

	void unlockScreen();

	MenuItemImage* btn_mainMenu;

	MenuItemImage* btn_setting;

	MenuItemImage* playButton;

	Sprite* diff_easy;

	Sprite* diff_medium;

	Sprite* diff_difficult;

	RankingList* rankingList;

	Layer* lockLayer;

	int lockCount;

	Sprite* ringIn;

	Sprite* ringOut;

	Sprite* lockText;
};

#endif