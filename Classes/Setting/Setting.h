#ifndef __SETTING_H__
#define __SETTING_H__

#include "cocos2d.h"

USING_NS_CC;

class Setting : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(Setting);

	void backToMainMenu();
private:
	MenuItemImage* btn_back;
};

#endif