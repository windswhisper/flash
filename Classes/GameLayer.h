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
    
    virtual void display();
    
    int x;
    
    int t;
    
    int type;
    
    int endt;

	Sprite* p;
};

class LongNote : public Note
{
public:
    virtual bool init();
    
    CREATE_FUNC(LongNote);
    
    static LongNote* createLongNote(int x,int t,int type,int endt);
    
    virtual void display();
    
    Sprite* lb;
    
    Sprite* lm;
    
    Sprite* le;
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
    
    void release(int col);
    
    void loadFile();
    
    void miss(int col);
    
    void getRate(int rate);
    
    float t;
    
	float speed;

	float offset;
    
    Vec2 key1Pos;
    
    float keyDis;
    
	char* musicFileName;

    Node* root;
    
    Sprite* board;
    
	Sprite* key[4];
    
    Sprite* pressLight[4];
    
    Sprite* hitEffect[4];
    
    Vector<Note*> notes;
    
    Vector<Note*> tags[4];

	Label* rate;

	Label* socre;
};

#endif
