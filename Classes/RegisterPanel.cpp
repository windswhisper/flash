#include "RegisterPanel.h"
#include "LoginPanel.h"

USING_NS_CC;


bool RegisterPanel::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();

	auto shadow = LayerColor::create(Color4B(0,0,0,168));

	this->addChild(shadow);

	bg_reg = Sprite::create("img/welcome/panel_regist.png");

	bg_reg->setPosition(Vec2(visiblesize.width / 2, visiblesize.height / 2));

	bg_reg->setScale(0);

	bg_reg->runAction(EaseBackOut::create(ScaleTo::create(0.5f, 1)));

	this->addChild(bg_reg);


	root = Node::create();

	root->setCascadeOpacityEnabled(true);

	root->setOpacity(0);

	root->runAction(Sequence::create(DelayTime::create(0.5f), FadeTo::create(0.5f, 255), NULL));

	this->addChild(root);

	auto content = Sprite::create("img/welcome/content_regist.png");

	content->setPosition(960, 650);

	root->addChild(content);


	this->btn_back = MenuItemImage::create("img/welcome/btn_back.png", "img/welcome/btn_back_p.png", CC_CALLBACK_0(RegisterPanel::log, this));

	this->btn_back->setPosition(Vec2(visiblesize.width/2-bg_reg->getContentSize().width/2+btn_back->getContentSize().width/2,visiblesize.height/2-bg_reg->getContentSize().height/2+btn_back->getContentSize().height/2));

	this->btn_reg = MenuItemImage::create("img/welcome/btn_regist.png", "img/welcome/btn_regist_p.png", CC_CALLBACK_0(RegisterPanel::reg, this));

	this->btn_reg->setPosition(Vec2(visiblesize.width / 2 + bg_reg->getContentSize().width / 2 - btn_back->getContentSize().width / 2, visiblesize.height / 2 - bg_reg->getContentSize().height / 2 + btn_back->getContentSize().height / 2));


	Menu* menu = Menu::create(btn_back, btn_reg, NULL);

	menu->setPosition(Point::ZERO);

	root->addChild(menu);

    return true;
}

void RegisterPanel::reg()
{
	
}

void RegisterPanel::close(CallFunc* callfunc)
{
    this->getEventDispatcher()->removeEventListenersForTarget(this,true);
	this->root->runAction(FadeTo::create(0.2f, 0));

	this->bg_reg->runAction(Sequence::create(DelayTime::create(0.2f), EaseSineIn::create(ScaleTo::create(0.3f, 0)),callfunc, CallFunc::create(CC_CALLBACK_0(RegisterPanel::removeFromParent, this)), NULL));

}

void RegisterPanel::log()
{
    this->close(CallFunc::create([=](){
        this->getParent()->addChild(LoginPanel::create());
    }));

}