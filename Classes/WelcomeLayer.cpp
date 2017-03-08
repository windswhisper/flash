#include "WelcomeLayer.h"
#include "LoginPanel.h"

bool WelcomeLayer::init()
{

	auto loginPanel = LoginPanel::create();

	loginPanel->setPosition(0, 0);

	this->addChild(loginPanel);
    
    //Sprite3D* sprite = Sprite3D::create("boss.obj");
	//sprite->setTexture("boss.png");
	//sprite->setScale(30);
	//sprite->setPosition3D(Vec3(500, 500, -2));
	//sprite->runAction(RotateBy::create(10, Vec3(0, 720, 0)));

	//this->addChild(sprite, 2);

    return true;
}
