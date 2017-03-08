#include "RegisterPanel.h"


bool RegisterPanel::init()
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
	
    return true;
}

void RegisterPanel::reg()
{
}

void RegisterPanel::close()
{
	this->root->runAction(FadeTo::create(0.2f, 0));

}
