#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Note : public Node
{
public:
    virtual void display()=0;
    
    virtual void miss()=0;
    
    virtual void click()=0;
    
    virtual void release()=0;
    
    void remove();
    
    int x;
    
    int t;
    
    int type;
    
    int endt;

};

class SimpleNote : public Note
{
public:
    virtual bool init();
    
    CREATE_FUNC(SimpleNote);
    
    static SimpleNote* createSimpleNote(int x,int t,int type,int endt);
    
    virtual void display();
    
    virtual void miss();
    
    virtual void click();
    
    virtual void release();
    
    Sprite* p;
    
};
class LongNote : public Note
{
public:
    virtual bool init();
    
    CREATE_FUNC(LongNote);
    
    static LongNote* createLongNote(int x,int t,int type,int endt);
    
    virtual void display();
    
    virtual void miss();
    
    virtual void click();
    
    virtual void release();
    
    void update(float dt);
    
    void finish();
    
    int status;//0=初始，1=按下，2=错过，3=完成
    
    float tSum;
    
    Vector<Sprite*> pics;
};

class GameLayer : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(GameLayer);
    
    static GameLayer* createWithId(int id,char* diff,char* name,int mode);
    
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
    
    void playAnimate(int col,int type);
    
    void comboIncrese();
    
    void comboClear();

    float t;
    
	float speed;

	float offset;
    
    Vec2 key1Pos;
    
    float keyDis;
    
    int songId;
    
    char filename[128];
    
    char diff[32];
    
    char songName[64];
    
    Node* root;
    
    Sprite* board;
    
	Sprite* key[4];
    
    Sprite* pressLight[4];
    
    Sprite* hitEffect[4];
    
    Vector<Note*> notes;
    
    Vector<Note*> tags[4];

	Sprite* rate;

    int score;
    
	Label* socreLabel;
    
    LabelAtlas* comboLabel;
    
    int combo;
    
    int rateCount[3];
};

static GameLayer* _gamelayer;
#endif
