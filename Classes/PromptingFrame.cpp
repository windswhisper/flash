#include "PromptingFrame.h"

bool PromptingFrame::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();


	promptingFrame = Sprite::create("img/promptingframe/promptingframe.png");

	promptingFrame->setPosition(visiblesize.width/2,visiblesize.height/2);

	this->addChild(promptingFrame);


	


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
	switch (messageTag)
	{
	case 1:
		strcpy(message, "Login Failed!");
		break;
	case 2:
		strcpy(message, "we need more gold!");
		break;
	}

	messageLabel = Label::create(message, "Arial", 72);

	messageLabel->setPosition(promptingFrame->getContentSize().width / 2, promptingFrame->getContentSize().height / 2);

	promptingFrame->addChild(messageLabel);
}

