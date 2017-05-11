#ifndef __PROMPTING_FRAME_H__
#define __PROMPTING_FRAME_H__

#include "cocos2d.h"

USING_NS_CC;

class PromptingFrame : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(PromptingFrame);

	void back();

	static PromptingFrame* createWithId(int messageTag);

	void setMessage(int messageTag);
private:
	Sprite* promptingFrame;

	Label* messageLabel;

	MenuItemImage* btn_back;

	char message[500];
};

#endif