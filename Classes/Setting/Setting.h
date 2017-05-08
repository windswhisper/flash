#ifndef __SETTING_H__
#define __SETTING_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class Setting : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(Setting);

	void backToMainMenu();

	void disableItem();

	void logout();

	void aboutUs();

//	virtual void onEnter() override;

private:
	MenuItemImage* btn_back;

	Sprite* bg;

	MenuItemImage* btn_disableItem;

	MenuItemImage* btn_aboutUs;

	MenuItemImage* btn_logout;

	Slider* musicVolume;

	Slider* keyPressVolume;

	Sprite* label_musicVolume;

	Sprite* label_keyPressVolume;
};

#endif