#include "LoginPanel.h"
#include "RegisterPanel.h"

bool LoginPanel::init()
{
	auto shadow = LayerColor::create(Color4B(0,0,0,168));

	this->addChild(shadow);

	bg = Sprite::create("img/welcome/panel_login.png");

	bg->setPosition(960, 540);

	bg->setScale(0);

	bg->runAction(EaseBackOut::create(ScaleTo::create(0.5f, 1)));

	this->addChild(bg);


	root = Node::create();

	root->setCascadeOpacityEnabled(true);

	root->setOpacity(0);

	root->runAction(Sequence::create(DelayTime::create(0.5f), FadeTo::create(0.5f, 255), NULL));

	this->addChild(root);

	auto content = Sprite::create("img/welcome/content_login.png");

	content->setPosition(960, 650);

	root->addChild(content);
	

	this->btn_login = MenuItemImage::create("img/welcome/btn_login.png", "img/welcome/btn_login_p.png", CC_CALLBACK_0(LoginPanel::login, this));

	this->btn_login->setPosition(1280, 196);

	this->btn_reg = MenuItemImage::create("img/welcome/btn_reg.png", "img/welcome/btn_reg_p.png", CC_CALLBACK_0(LoginPanel::reg, this));

	this->btn_reg->setPosition(1920-1280, 196);


	Menu* menu = Menu::create(btn_login, btn_reg, NULL);      

	menu->setPosition(Point::ZERO);     

	root->addChild(menu);

    return true;
}

void LoginPanel::login()
{
}

void LoginPanel::close()
{
	this->root->runAction(FadeTo::create(0.2f, 0));

    this->bg->runAction(Sequence::create(DelayTime::create(0.2f), EaseSineIn::create(ScaleTo::create(0.3f, 0)), CallFunc::create(CC_CALLBACK_0(LoginPanel::removeFromParent,this)),NULL));

}
 
void LoginPanel::reg()
{
	this->close();

	this->getParent()->addChild(RegisterPanel::create());
}