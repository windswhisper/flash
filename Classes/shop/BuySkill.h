#ifndef __SKILL_H__
#define __SHILL_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ShopItemInfo.h"

USING_NS_CC;
using namespace ui;

class BuySkill : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(BuySkill);

	void skillSelect(char* skillId);

	void setSkill();

	Button* skill[10];

	ScrollView* scrollView;

	ShopItemInfo* skillInfo;

	char skillID[3][20];
};

#endif
