#ifndef __PK_GAMEOVER_LAYER_H__
#define __PK_GAMEOVER_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class PKGameOverLayer : public Layer
{
public :
	virtual bool init();

	CREATE_FUNC(PKGameOverLayer);

	void backToPK();

	void close(CallFunc* callfunc);

	void setData(char* songName,char* songDiff,char* winnerName,const char* loserName,int winnerScore,int winnerCombo,int winnerAcc,int loserScore,int loserCombo,int loserAcc,int winnerGrade,int loserGrade);

	void setGrade(int score,int combo,int acc,bool isMine,int playerGrade);

private:
	Sprite* PK_bg;

	Sprite* songsNameFrame;

	Sprite* winnerNameFrame;

	Sprite* loserNameFrame;

	Sprite* PK_vs;

	Sprite* myGradeFrame;

	Sprite* opnGradeFrame;

	Sprite* winner;

	Sprite* loser;

	Sprite* evaluation;

	Button* back;

	char winner_score[16];

	char winner_combo[8];

	char winner_acc[5];

	//Label* label_songName;

	//Label* label_songDiff;

	//Label* label_winnerName;

	//Label* label_loserName;
};

#endif
