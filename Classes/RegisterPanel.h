#ifndef __LOGIN_PANEL_H__
#define __LOGIN_PANEL_H__

#include "cocos2d.h"

USING_NS_CC;


class RegisterPanel : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(RegisterPanel);

	void reg();

	void close();

	Sprite* bg;

	Node* root;

	MenuItemImage* btn_login;

	MenuItemImage* btn_reg;
    
};

#endif
