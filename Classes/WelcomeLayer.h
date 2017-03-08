#ifndef __WELCOME_LAYER_H__
#define __WELCOME_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(WelcomeLayer);

	Sprite* bg;
    


};

#endif
