#include "WelcomeLayer.h"
#include "LoginPanel.h"

bool WelcomeLayer::init()
{
	this->bg = Sprite::create("img/welcome/bg_welcome.png");

	this->bg->setPosition(960, 540);

	this->bg->setGlobalZOrder(-1);
	this->addChild(this->bg);

	auto loginPanel = LoginPanel::create();

	loginPanel->setPosition(0, 0);

	this->addChild(loginPanel);

	auto sp = Sprite::create("sp.png");
	sp->setPosition(900, 500);
	sp->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1,1.1), ScaleTo::create(0.4, 1),NULL)));
	sp->runAction(RepeatForever::create(Sequence::create(RotateBy::create(2, Vec3(0, 40, 0)), RotateBy::create(4, Vec3(0, -80, 0))	, RotateBy::create(2, Vec3(0, 40, 0)), NULL)));
	this->addChild(sp);

	//Sprite3D* sprite = Sprite3D::create("boss.obj");
	//sprite->setTexture("boss.png");
	//sprite->setScale(30);
	//sprite->setPosition3D(Vec3(500, 500, -2));
	//sprite->runAction(RotateBy::create(10, Vec3(0, 720, 0)));

	//this->addChild(sprite, 2);

    return true;
}
