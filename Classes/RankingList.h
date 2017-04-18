#ifndef _RANGING_LIST_H_
#define _RANKING_LIST_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;
using namespace ui;
using namespace std;

struct RankInfo
{
	char name[32];

	char score[16];

	char comble[8];
};

class RankingList : public Node
{
public:
	virtual bool init();

	CREATE_FUNC(RankingList);

	void setData(vector<RankInfo*> rankItem,RankInfo* localItem);

	void addData(const char* name, const char* score, const char* comble);

	Sprite* setLabel(const char* name, const char* score, const char* comble,bool ismine);

private:
	Sprite * bg;

//	Vector<Sprite*> rankitem;

	ListView* listview;

//	char RankInfo[20][3][32];
	vector<RankInfo*> rankItem;

	RankInfo* localItem;
};

#endif