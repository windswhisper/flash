#ifndef __PK_GAMEOVER_LAYER_H__
#define __PK_GAMEOVER_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class PKGameOverLayer : public Layer
{
public :
	virtual bool init();

	CREATE_FUNC(PKGameOverLayer);

	void backToPK();

	void playAgain();

	void setData(char* songName,char* songDiff,char* winnerName,char* loserName,int winnerScore,int winnerCombo,int winnerAcc,int loserScore,int loserCombo,int loserAcc);

private:
	Sprite* PK_bg;

	Sprite* songsNameFrame;

	Sprite* winnerNameFrame;

	Sprite* loserNameFrame;

	Sprite* PK_vs;

	Sprite* winnerGrade;

	Sprite* loserGrade;

	Sprite* winner;

	Sprite* loser;

	char winner_score[16];

	char winner_combo[8];

	char winner_acc[5];

	//Label* label_songName;

	//Label* label_songDiff;

	//Label* label_winnerName;

	//Label* label_loserName;
};

#endif