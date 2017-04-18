#include "PKSelectDiff.h"
#include "MainMenuLayer.h"

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

	playButton->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.4f, 1), NULL)));

	Menu* menu = Menu::create(btn_mainMenu,btn_setting,playButton,NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);


	auto ornament = Sprite::create("img/PK/ornament.png");

	ornament->setPosition(330,520);

	this->addChild(ornament);


	rankingList = RankingList::create();

	rankingList->setPosition(400,520);

	this->addChild(rankingList);

	
	this->setDiff();

	this->lockLayer = Layer::create();

	ringIn = Sprite::create("img/loading/loadingRingIn.png");

	ringIn->setPosition(100, 100);

	lockLayer->addChild(ringIn);

	ringOut = Sprite::create("img/loading/loadingRingOut.png");

	ringOut->setPosition(100, 100);

	lockLayer->addChild(ringOut);

	lockText = Sprite::create("img/loading/loadingText.png");

	lockText->setPosition(340, 70);

	lockLayer->addChild(lockText);

	this->addChild(this->lockLayer, 127);

	auto listener1 = EventListenerTouchOneByOne::create();

	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, lockLayer);

	this->lockCount = 1;

	this->unlockScreen();


	return true;
}

void PKSelectDiff::setDiff()
{
	diff_easy = Sprite::create("img/PK/easy.png");

	diff_easy->setPosition(Vec2(1000,500));

	diff_easy->setScale(1.1);

	this->addChild(diff_easy,3);


	diff_medium = Sprite::create("img/PK/medium.png");

	diff_medium->setPosition(Vec2(1300, 300));

	this->addChild(diff_medium, 2);


	diff_difficult = Sprite::create("img/PK/difficult.png");

	diff_difficult->setPosition(Vec2(1300, 700));

	this->addChild(diff_difficult, 1);

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
			diff_easy->setZOrder(100);
			diff_medium->setZOrder(0);
			diff_difficult->setZOrder(0);
			log("diff_easy");
			diff_easy->runAction(MoveTo::create(1.0f,Vec2(1000,500)));
			diff_medium->runAction(MoveTo::create(1.0f, Vec2(1300, 300)));
			diff_difficult->runAction(MoveTo::create(1.0f, Vec2(1300, 700)));
		}

		else if (target == diff_medium)
		{
			diff_easy->setZOrder(0);
			diff_medium->setZOrder(100);
			diff_difficult->setZOrder(0);
			log("diff_medium");
			diff_medium->runAction(MoveTo::create(1.0f, Vec2(1000, 500)));
			diff_difficult->runAction(MoveTo::create(1.0f, Vec2(1300, 300)));
			diff_easy->runAction(MoveTo::create(1.0f, Vec2(1300, 700)));
		}

		else
		{
			diff_easy->setZOrder(0);
			diff_medium->setZOrder(0);
			diff_difficult->setZOrder(100);
			log("diff_difficult");
			diff_difficult->runAction(MoveTo::create(1.0f, Vec2(1000, 500)));
			diff_easy->runAction(MoveTo::create(1.0f, Vec2(1300, 300)));
			diff_medium->runAction(MoveTo::create(1.0f, Vec2(1300, 700)));
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,diff_easy);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), diff_medium);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), diff_difficult);
}

void PKSelectDiff::backToMenu()
{
	this->removeAllChildren();

	this->getParent()->addChild(MainMenuLayer::create());
}

void PKSelectDiff::setting()
{

}

void PKSelectDiff::matching()
{
	this->lockScreen();
}

void PKSelectDiff::lockScreen()
{
	lockCount++;

	if (lockCount>1)return;

	this->addChild(this->lockLayer, 127);

	ringIn->runAction(RepeatForever::create(RotateBy::create(4, 360)));

	ringOut->runAction(RepeatForever::create(RotateBy::create(4, -360)));
}

void PKSelectDiff::unlockScreen()
{
	lockCount--;

	if (lockCount>0)return;

	this->lockLayer->retain();
	this->lockLayer->removeFromParent();
}