#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

USING_NS_CC;
using namespace ui;

class GameOver : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(GameOver);

	void setData(char* songsName, char* songsDiff, int score, int combo, int acc, int miss, int poor, int good, int cool);

	void back();

	void playAgain();

	Size visiblesize;

	MenuItemImage* btn_back;

	MenuItemImage* btn_playAgain;

	Sprite* songsNameFrame;

	Sprite* mainFrame;

	Sprite* accFrame;

	Sprite* pictureFrame;

	Sprite* scoreFrame;

	Sprite* evaluation;
};

#endif