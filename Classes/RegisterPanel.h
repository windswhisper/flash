#ifndef __REGISTER_PANEL_H__
#define __REGISTER_PANEL_H__

#include "cocos2d.h"
#include "SocketClient.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace ui;

class RegisterPanel : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(RegisterPanel);

	void reg();

	void close(CallFunc* callfunc);

	void log();

	Sprite* bg_reg;

	Node* root;

	MenuItemImage* btn_back;

	MenuItemImage* btn_reg;
    
    TextField* usernameText;
    
    TextField* passwordText;
};

#endif
