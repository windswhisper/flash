#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    static GameScene* getInstance();
    
    void lockScreen();
    
    void unlockScreen();
    
    Sprite* bg;
    
    Layer* lockLayer;
    
    int lockCount;
    
    Sprite* ringIn;
    
    Sprite* ringOut;
    
    Sprite* lockText;
};
static GameScene* _gamescene;

#endif
