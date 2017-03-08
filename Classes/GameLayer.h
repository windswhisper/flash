#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Note : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(Note);
    
    static Note* createNote(int x,int t,int type,int endt);
    
    int x;
    
    int t;
    
    int type;
    
    int endt;

	Sprite* p;
};

class GameLayer : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(GameLayer);
    
    void update(float dt);
    
    bool onTouchBegan(Touch *touch, Event *pEvent);
    
    void onTouchMoved(Touch *touch, Event *pEvent);
    
    void onTouchEnded(Touch *touch, Event *pEvent);
    
    void onKeyPressed(EventKeyboard::KeyCode keyCode,Event* event);
    
    void onKeyReleased(EventKeyboard::KeyCode keyCode,Event* event);
    
    void dropTag(int col);
    
    void click(int col);
    
    void loadFile();
    
    float t;
    
	float speed;

	float offset;

	char* musicFileName;

    Node* board;
    
	Sprite* key[4];
    
    Vector<Note*> notes;
    
    Vector<Note*> tags[4];

	Label* rate;

	Label* socre;
};

#endif
