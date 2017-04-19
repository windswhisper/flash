#include "RankingList.h"

#include "SongsLayer.h"
#include "SongsListView.h"
#include "SocketIOClient.h"

bool RankingList::init()
{
	//for (int i = 0; i <= 20; ++i)
	//{
	//	strcpy(RankInfo[i][0] ,"Ranklist");
	//	strcpy(RankInfo[i][1] , "123456");
	//	strcpy(RankInfo[i][2] , "900x");
	//}
	/*localItem = new RankInfo();
	strcpy(localItem->name, "localName");
	strcpy(localItem->score, "999999");
	strcpy(localItem->comble, "100x");

	for (int i = 0; i < 20; ++i)
	{
		auto rankInfo = new RankInfo();

		strcpy(rankInfo->name, "RankList");

		strcpy(rankInfo->score, "123456");

		strcpy(rankInfo->comble, "900x");

		rankItem.push_back(rankInfo);
	}*/

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

    myScore = Node::create();
    
    this->addChild(myScore);
    
	//this->setData(rankItem,localItem);

	
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

void RankingList::load(int songId,char* diffName)
{
    this->listview->removeAllItems();
    myScore->removeAllChildren();
    
    char msg[128];
    sprintf(msg, "{\"songId\":%d,\"diffName\":\"%s\"}",songId,diffName);
    SocketIOClient::getInstance()->send("scoreList",msg);
    SocketIOClient::getInstance()->listen("scoreListRes", [=](SIOClient* client, std::string msg){
        rapidjson::Document doc;
        doc.Parse<0>(msg.c_str());
        
        for (int i = 0; i < doc["list"].Size(); i++)
        {
            this->addData(doc["list"][i]["username"].GetString(),doc["list"][i]["score"].GetInt(),doc["list"][i]["combo"].GetInt());
        }
        if(doc["my"].Size()>0)
        {
            auto sprite_local = setLabel(doc["my"][0]["username"].GetString(),doc["my"][0]["score"].GetInt(),doc["my"][0]["combo"].GetInt(), true);
            
            sprite_local->setPosition(0, -185);
            
            sprite_local->setColor(Color3B::GREEN);
            
            myScore->addChild(sprite_local);
        }
    });
}

void RankingList::setData(vector<RankInfo*> rankItem, RankInfo* localItem)
{

}

Sprite* RankingList::setLabel(const char* name, int score, int combo, bool ismine)
{
	auto sprite = Sprite::create("img/selectsongs/RankingList_Score.png");

	sprite->setContentSize(Size(480, 60));

	auto label_name = Label::createWithSystemFont(name, "", 36);

	label_name->setAnchorPoint(Vec2(0, 0));

	label_name->setPosition(0, 10);

	sprite->addChild(label_name);

    char str[32];
    
    sprintf(str, "%d",score);
    
	auto label_score = Label::createWithSystemFont(str, "", 36);

	label_score->setAnchorPoint(Vec2(0, 0));

	label_score->setPosition(160, 10);

	sprite->addChild(label_score);
    
    sprintf(str, "%d×",combo);
    
	auto label_comble = Label::createWithSystemFont(str, "", 36);

	label_comble->setAnchorPoint(Vec2(0, 0));

	label_comble->setPosition(320, 10);

	sprite->addChild(label_comble);
	
	return sprite;
}

void RankingList::addData(const char* name, int score, int combo)
{
	auto sprite = setLabel(name, score, combo,false);

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
