#ifndef __LOGIN_PANEL_H__
#define __LOGIN_PANEL_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class LoginPanel : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(LoginPanel);

	void login();

	void close(CallFunc* callfunc);

	void reg();

	Sprite* bg;

	Node* root;

	MenuItemImage* btn_login;

	MenuItemImage* btn_reg;
    
    TextField* usernameText;
    
    TextField* passwordText;
};

#endif
