#include "RankingList.h"

#include "SongsLayer.h"
#include "SongsListView.h"

bool RankingList::init()
{
	//for (int i = 0; i <= 20; ++i)
	//{
	//	strcpy(RankInfo[i][0] ,"Ranklist");
	//	strcpy(RankInfo[i][1] , "123456");
	//	strcpy(RankInfo[i][2] , "900x");
	//}

	for (int i = 0; i < 21; ++i)
	{
		auto rankInfo = new RankInfo();

		strcpy(rankInfo->name, "RankList");

		strcpy(rankInfo->score, "123456");

		strcpy(rankInfo->comble, "900x");

		rankItem.push_back(rankInfo);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->bg = Sprite::create("img/selectsongs/RankingList_bg.png");

	this->bg->setPosition(Point::ZERO);

	this->addChild(bg);

	listview = ListView::create();

	listview->setDirection(ScrollView::Direction::VERTICAL);

	listview->setBounceEnabled(true);

//	listview->setBackGroundImage("img/2.jpg");

	listview->setBackGroundImageScale9Enabled(true);

	listview->setSize(Size(480, 300));

	listview->setAnchorPoint(Vec2(0.5, 0.5));

	listview->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 2 - 8));

	bg->addChild(listview);

	this->setData(rankItem);

	
/*
	for (int i = 0; i < 20; ++i)
	{
		char info[50];

		sprintf(info,"RankingList\%d",i);

		this->addData(info);
	}
*/
	return true;

}

void RankingList::setData(vector<RankInfo*> rankItem)
{
	for (int i = 0; i < 20; ++i)
	{
		char* name = rankItem[i]->name;

		char* score = rankItem[i]->score;

		char* comble = rankItem[i]->comble;

		this->addData(name,score,comble);
	}
	auto sprite_local = setLabel(rankItem[20]->name, rankItem[20]->score, rankItem[20]->comble, true);

//	sprite->setAnchorPoint(Vec2(0, 0));

	sprite_local->setPosition(0, -185);

	sprite_local->setColor(Color3B::GREEN);

	this->addChild(sprite_local);
}

Sprite* RankingList::setLabel(const char* name, const char* score, const char* comble, bool ismine)
{
	auto sprite = Sprite::create("img/selectsongs/RankingList_Score.png");

	sprite->setContentSize(Size(480, 60));

	auto label_name = Label::createWithSystemFont(name, "", 36);

	label_name->setAnchorPoint(Vec2(0, 0));

	label_name->setPosition(0, 10);

	sprite->addChild(label_name);

	auto label_score = Label::createWithSystemFont(score, "", 36);

	label_score->setAnchorPoint(Vec2(0, 0));

	label_score->setPosition(160, 10);

	sprite->addChild(label_score);

	auto label_comble = Label::createWithSystemFont(comble, "", 36);

	label_comble->setAnchorPoint(Vec2(0, 0));

	label_comble->setPosition(320, 10);

	sprite->addChild(label_comble);
	
	return sprite;
}

void RankingList::addData(const char* name, const char* score, const char* comble)
{
	auto sprite = setLabel(name, score, comble,false);

	Layout* item = Layout::create();

	item->setContentSize(sprite->getContentSize());

	sprite->setPosition(Vec2(item->getContentSize().width/2,item->getContentSize().height/2));

	item->addChild(sprite);

	listview->addChild(item);
/*	Layout* layout = Layout::create();

	auto title = Label::createWithCharMap("img/selectsongs/RankingList_Score.png", 120,80, '0');

	title->setString(name);

	layout->addChild(title);

	listview->setItemModel(item);

	for (int j = 0; j < 3; ++j)
	{
		listview->pushBackDefaultItem();
	}

	for (int j = 0; j < 3; ++j)
	{
		listview->insertDefaultItem(0);
	}
	*/
}
