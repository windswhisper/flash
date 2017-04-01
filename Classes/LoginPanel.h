#ifndef __LOGIN_PANEL_H__
#define __LOGIN_PANEL_H__

#include "cocos2d.h"
//#include "cocos-ext.h"


USING_NS_CC;
//USING_NS_CC_EXT;

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
    
};

#endif
