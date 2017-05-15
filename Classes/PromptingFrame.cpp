#include "PromptingFrame.h"

bool PromptingFrame::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();

    
    auto bg = LayerColor::create(Color4B(0,0,0,72));
    
    this->addChild(bg);
    
    
	promptingFrame = Sprite::create("img/promptingframe/promptingframe.png");

	promptingFrame->setPosition(visiblesize.width/2,visiblesize.height/2);

    promptingFrame->setScale(0);
    
    promptingFrame->runAction(EaseBackOut::create(ScaleTo::create(0.5f, 1)));
    
	this->addChild(promptingFrame);

    

    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](Touch* touch,Event* event){
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	btn_back = MenuItemImage::create("img/promptingframe/confirme.png","img/promptingframe/confirme_p.png",CC_CALLBACK_0(PromptingFrame::back,this));

	btn_back->setPosition(promptingFrame->getContentSize().width/2, btn_back->getContentSize().height / 2 + 100);

	Menu* menu = Menu::create(btn_back,NULL);

	menu->setPosition(Point::ZERO);

	promptingFrame->addChild(menu);


	return true;
}

PromptingFrame* PromptingFrame::createWithId(int messageTag)
{
//	char message[500];

	PromptingFrame* promptingFrame = PromptingFrame::create();

	promptingFrame->setMessage(messageTag);

	return promptingFrame;
}

void PromptingFrame::back()
{
	this->removeFromParent();
}

void PromptingFrame::setMessage(int messageTag)
{
	/*switch (messageTag)
	{
        case 1:
            strcpy(message, "用户名或密码错误！");
            break;
        case 2:
            strcpy(message, "金币余额不足!");
            break;
        case 3:
            strcpy(message, "用户名已被注册");
            break;
        case 4:
            strcpy(message, "用户名不能为空！");
            break;
        case 5:
            strcpy(message, "密码不能为空！");
            break;
        case 6:
            strcpy(message, "购买成功!");
            break;
	}
*/
	messageLabel = Label::create(message, "Arial", 72);

	messageLabel->setPosition(promptingFrame->getContentSize().width / 2, promptingFrame->getContentSize().height*0.6f);

	promptingFrame->addChild(messageLabel);
}

