#ifndef __SONGS_PACKAGE_H__
#define __SONGS_PACKAGE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ShopItemInfo.h"

USING_NS_CC;
using namespace ui;

class SongsPackage : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(SongsPackage);

	void songsPackageSelect(char* songsPackageID);

	void setSongspackage();

	ScrollView* scrollView;

	Button* songsPackage[20];

	ShopItemInfo* songspackageinfo;

	char songsPackageID[8][20];
};

#endif