#include "RegisterPanel.h"
#include "LoginPanel.h"
#include "MainMenuLayer.h"

#include "SocketIOClient.h"

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

    
    this->usernameText = TextField::create();
    
    this->usernameText->setFontSize(64);
    
    this->usernameText->setTextAreaSize(Size(600,100));
    
    this->usernameText->setPosition(Vec2(873,690));
    
    this->usernameText->setMaxLengthEnabled(true);
    
    this->usernameText->setMaxLength(10);
    
    this->usernameText->setPlaceHolder("Username");
    
    this->usernameText->setAnchorPoint(Vec2(0,0.5));
        
    root->addChild(this->usernameText);
    
    this->passwordText = TextField::create();
    
    this->passwordText->setFontSize(64);
    
    this->passwordText->setPosition(Vec2(873,580));
    
    this->passwordText->setTextAreaSize(Size(600,100));
    
    this->passwordText->setMaxLengthEnabled(true);
    
    this->passwordText->setMaxLength(12);
    
    this->passwordText->setPlaceHolder("Password");
    
    this->passwordText->setAnchorPoint(Vec2(0,0.5));
    
    this->passwordText->setPasswordEnabled(true);
    
    root->addChild(this->passwordText);
    
    
	Menu* menu = Menu::create(btn_back, btn_reg, NULL);

	menu->setPosition(Point::ZERO);

	root->addChild(menu);

    return true;
}

void RegisterPanel::reg()
{
    char msg[128];
    sprintf(msg, "{\"username\":\"%s\",\"password\":\"%s\"}",this->usernameText->getString().c_str(),this->passwordText->getString().c_str());
    SocketIOClient::getInstance()->send("register",msg);
    SocketIOClient::getInstance()->lock();
    SocketIOClient::getInstance()->listen("registerRes", [=](SIOClient* client, std::string msg){
        if(msg.compare("succeed")==0)
        {
            this->close(CallFunc::create([=](){
                this->getParent()->addChild(MainMenuLayer::create());
            }));
        }
        if(msg.compare("fail")==0)
        {
            //TODO
        }
        SocketIOClient::getInstance()->unlock();    });
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
