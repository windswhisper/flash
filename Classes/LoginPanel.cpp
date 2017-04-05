#include "LoginPanel.h"
#include "RegisterPanel.h"
#include "MainMenuLayer.h"
#include "SocketIOClient.h"

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

    
    this->usernameText = TextField::create();
    
    this->usernameText->setFontSize(64);
    
    this->usernameText->setTextAreaSize(Size(600,100));
    
    this->usernameText->setPosition(Vec2(800,633));
    
    this->usernameText->setMaxLengthEnabled(true);
    
    this->usernameText->setMaxLength(10);
    
    this->usernameText->setPlaceHolder("请输入用户名");
    
    this->usernameText->setAnchorPoint(Vec2(0,0.5));
    
    root->addChild(this->usernameText);
    
    this->passwordText = TextField::create();
    
    this->passwordText->setFontSize(64);
    
    this->passwordText->setPosition(Vec2(800,520));
    
    this->passwordText->setTextAreaSize(Size(600,100));
    
    this->passwordText->setMaxLengthEnabled(true);
    
    this->passwordText->setMaxLength(12);
    
    this->passwordText->setPlaceHolder("请输入密码");
    
    this->passwordText->setAnchorPoint(Vec2(0,0.5));
    
    this->passwordText->setPasswordEnabled(true);
    
    root->addChild(this->passwordText);
    
    
    return true;
}

void LoginPanel::login()
{
    char msg[128];
    sprintf(msg, "{\"username\":\"%s\",\"password\":\"%s\"}",this->usernameText->getString().c_str(),this->passwordText->getString().c_str());
    SocketIOClient::getInstance()->send("login",msg);
    SocketIOClient::getInstance()->listen("loginRes", [=](SIOClient* client, std::string msg){
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
    });

    
}

void LoginPanel::close(CallFunc* callfunc)
{
    this->getEventDispatcher()->removeEventListenersForTarget(this,true);
	this->root->runAction(FadeTo::create(0.2f, 0));

    this->bg->runAction(Sequence::create(DelayTime::create(0.2f), EaseSineIn::create(ScaleTo::create(0.3f, 0)),callfunc, CallFunc::create(CC_CALLBACK_0(LoginPanel::removeFromParent,this)),NULL));

}
 
void LoginPanel::reg()
{
    this->close(CallFunc::create([=](){
        this->getParent()->addChild(RegisterPanel::create());
    }));
	
}
