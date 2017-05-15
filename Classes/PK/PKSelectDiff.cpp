#include "PKSelectDiff.h"
#include "MainMenuLayer.h"
#include "SocketIOClient.h"
#include "GameLayer.h"
#include "../Setting/Setting.h"

bool PKSelectDiff::init()
{
	btn_mainMenu = MenuItemImage::create("img/selectsongs/btn_mainmenu.png", "img/selectsongs/btn_mainmenu_p.png", CC_CALLBACK_0(PKSelectDiff::backToMenu, this));

	btn_mainMenu->setPosition(250, 973 + 300);

	btn_mainMenu->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1, Vec2(0, -300)))), NULL));

	auto ringL = Sprite::create("img/selectsongs/ring.png");

	ringL->setPosition(130, 98);

	ringL->runAction(RepeatForever::create(RotateBy::create(4, 360)));

	btn_mainMenu->addChild(ringL);



	btn_setting = MenuItemImage::create("img/selectsongs/btn_setting.png", "img/selectsongs/btn_setting_p.png", CC_CALLBACK_0(PKSelectDiff::setting, this));

	btn_setting->setPosition(1670, 973 + 300);

	btn_setting->runAction(Sequence::create(DelayTime::create(0.5f), (EaseSineOut::create(MoveBy::create(0.5f, Vec2(0, -300)))), NULL));

	auto ringR = Sprite::create("img/selectsongs/ring.png");

	ringR->setPosition(357, 96);

	ringR->runAction(RepeatForever::create(RotateBy::create(4, 360)));

	btn_setting->addChild(ringR);

	playButton = MenuItemImage::create("img/selectsongs/btn_play.png", "img/selectsongs/btn_play.png", CC_CALLBACK_0(PKSelectDiff::matching, this));

	playButton->setPosition(1850, 110);
    
    this->playButton->setOpacity(0);
    
    this->playButton->runAction(FadeTo::create(0.5f,255));
    
	playButton->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.4f, 1), NULL)));

	Menu* menu = Menu::create(btn_mainMenu,btn_setting,playButton,NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	
	ornament = Sprite::create("img/PK/ornament.png");

	ornament->setPosition(-430,520);

	ornament->runAction(Sequence::create(Spawn::create(DelayTime::create(0.2f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(700, 0)))), NULL), NULL));

	this->addChild(ornament);


	rankingList = RankingList::create();

	rankingList->setPosition(400,345);

	ornament->addChild(rankingList);

	
	this->setDiff();


	return true;
}

void PKSelectDiff::setDiff()
{
	diff_easy = Sprite::create("img/PK/easy.png");

	diff_easy->setPosition(Vec2(2500,500));

	diff_easy->setScale(1.1);

	diff_easy->runAction(Sequence::create(DelayTime::create(0.2f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(-1500, 0)))), NULL));

	this->addChild(diff_easy,3);


	diff_medium = Sprite::create("img/PK/medium.png");

	diff_medium->setPosition(Vec2(1300, -300));

	diff_medium->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(0, 600)))), NULL));

	this->addChild(diff_medium, 2);


	diff_difficult = Sprite::create("img/PK/difficult.png");

	diff_difficult->setPosition(Vec2(1300, 1300));

	diff_difficult->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(0, -600)))), NULL));

	this->addChild(diff_difficult, 1);


	diffMid = diff_easy;

	diffUp = diff_difficult;

	diffDown = diff_medium;


	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch* touch, Event* event){

		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertToNodeSpace(touch->getLocation());

		Size s = target->getContentSize();

		Rect rect = Rect(0,0,s.width,s.height);

		if (rect.containsPoint(locationInNode))
		{
			target->setOpacity(180);

			return true;
		}
		return false;
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event){

		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		target->setOpacity(255);

		if (target == diff_easy)
		{
			this->diffAction(diff_difficult, diff_easy, diff_medium);
		}

		else if (target == diff_medium)
		{
			this->diffAction(diff_easy, diff_medium, diff_difficult);
		}

		else
		{
			this->diffAction(diff_medium, diff_difficult, diff_easy);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,diff_easy);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), diff_medium);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), diff_difficult);
}

void PKSelectDiff::diffAction(Sprite* up, Sprite* mid, Sprite* down)
{
	diffUp = up;
	diffMid = mid;
	diffDown = down;
	diffUp->setZOrder(0);
	diffMid->setZOrder(1);
	diffDown->setZOrder(0);
	diffUp->setScale(1);
	diffMid->setScale(1.1);
	diffDown->setScale(1);
	diffUp->stopAllActions();
	diffMid->stopAllActions();
	diffDown->stopAllActions();
	diffMid->runAction(MoveTo::create(0.5f, Vec2(1000, 500)));
	diffDown->runAction(MoveTo::create(0.5f, Vec2(1300, 300)));
	diffUp->runAction(MoveTo::create(0.5f, Vec2(1300, 700)));
}

void PKSelectDiff::backToMenu()
{
	this->close(CallFunc::create([=]()
	{
		this->getParent()->addChild(MainMenuLayer::create());
	}));
}

void PKSelectDiff::setting()
{
	this->close(CallFunc::create([=]()
	{
		this->getParent()->addChild(Setting::create());
	}));
}

void PKSelectDiff::matching()
{
    SocketIOClient::getInstance()->send("match","");
    SocketIOClient::getInstance()->lock();
    SocketIOClient::getInstance()->listen("matchRes", [=](SIOClient* client, std::string msg){

        
		this->close(CallFunc::create([=](){
			rapidjson::Document doc;
            doc.Parse<0>(msg.c_str());

            int songId = doc["songId"].GetInt();
            char diffName[64];
            strcpy(diffName, doc["diffName"].GetString());
            
            char songName[64];
            strcpy(songName, doc["name"].GetString());
            
            this->getParent()->addChild(GameLayer::createWithId(songId,songName , diffName, 1));
        }));
        SocketIOClient::getInstance()->unlock();
    });
}

void PKSelectDiff::close(CallFunc* callfunc)
{
	this->getEventDispatcher()->removeEventListenersForTarget(this, true);

	
	diffMid->runAction(Sequence::create(DelayTime::create(0.2f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(1500, 0)))), NULL));

	diffDown->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(0, -600)))), NULL));

	diffUp->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(0, 600)))), NULL));

	ornament->runAction(Sequence::create(Spawn::create(DelayTime::create(0.2f), (EaseSineOut::create(MoveBy::create(1.0f, Vec2(-700, 0)))),NULL), NULL));

	btn_mainMenu->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1, Vec2(0, 300)))), NULL));

	btn_setting->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1, Vec2(0, 300)))), callfunc, CallFunc::create(CC_CALLBACK_0(PKSelectDiff::removeFromParent, this)), NULL));
    
    this->playButton->runAction(FadeTo::create(0.5f,0));
}
