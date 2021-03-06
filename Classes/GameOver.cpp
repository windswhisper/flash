#include "GameOver.h"

#include "GameLayer.h"
#include "SongsLayer.h"
#include "SocketIOClient.h"
#include "UserInfo.h"

bool GameOver::init()
{
	visiblesize = Director::getInstance()->getVisibleSize();


	songsNameFrame = Sprite::create("img/GameOver/songsInfo_frame.png");

	songsNameFrame->setPosition(Vec2(songsNameFrame->getContentSize().width / 2 - 17, visiblesize.height - songsNameFrame->getContentSize().height / 2 + 13));

	this->addChild(songsNameFrame);

	
	mainFrame = Sprite::create("img/GameOver/middle_frame.png");

//	mainFrame->setScale(0.8);

	mainFrame->setPosition(Vec2(visiblesize.width/2,visiblesize.height/2));

	this->addChild(mainFrame);


	pictureFrame = Sprite::create("img/GameOver/frame.png");

	pictureFrame->setPosition(Vec2(400,538));

	this->addChild(pictureFrame);


	scoreFrame = Sprite::create("img/GameOver/score.png");

	scoreFrame->setPosition(Vec2(1220,800));

	this->addChild(scoreFrame);


	accFrame = Sprite::create("img/GameOver/ACC_frame.png");

	accFrame->setPosition(Vec2(accFrame->getContentSize().width/2 - 17,accFrame->getContentSize().height/2 - 15));

	this->addChild(accFrame);

	auto combo = Sprite::create("img/GameOver/combo.png");

	combo->setPosition(300,100);

	accFrame->addChild(combo);

	auto Acc = Sprite::create("img/GameOver/ACC.png");

	Acc->setPosition(1200,100);

	accFrame->addChild(Acc);


	auto miss = Sprite::create("img/GameOver/miss.png");

	miss->setPosition(Vec2(900,285));

	this->addChild(miss);

	auto poor = Sprite::create("img/GameOver/poor.png");

	poor->setPosition(Vec2(900, 410));

	this->addChild(poor);

	auto good = Sprite::create("img/GameOver/good.png");

	good->setPosition(Vec2(900, 535));

	this->addChild(good);

	auto cool = Sprite::create("img/GameOver/cool.png");

	cool->setPosition(Vec2(900, 660));

	this->addChild(cool);

	
	btn_playAgain = MenuItemImage::create("img/GameOver/btn_playAgain.png", "img/GameOver/btn_playAgain_p.png", CC_CALLBACK_0(GameOver::playAgain, this));

	btn_playAgain->setPosition(Vec2(visiblesize.width - btn_playAgain->getContentSize().width / 2 + 7, visiblesize.height - btn_playAgain->getContentSize().height / 2));


	btn_back = MenuItemImage::create("img/GameOver/btn_back.png", "img/GameOver/btn_back_p.png", CC_CALLBACK_0(GameOver::back, this));

	btn_back->setPosition(Vec2(visiblesize.width - btn_back->getContentSize().width / 2 + 10, btn_back->getContentSize().height / 2 - 10));


	Menu* menu = Menu::create(btn_back,btn_playAgain,NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);


	return true;
}

void GameOver::setData(int songId,char* songsName, char* songsDiff,int grade, int score, int combo, int acc, int miss, int poor, int good, int cool)
{
    this->songId = songId;
    strcpy(this->songName, songsName);
    strcpy(this->diffName, songsDiff);
    
	//	char name[20] = "Flower Dance";
	auto label_songsName = Label::createWithSystemFont(songsName, "", 98);

	label_songsName->setPosition(350, 100);

	songsNameFrame->addChild(label_songsName);


	auto label_songsDiff = Label::createWithSystemFont(songsDiff, "", 98);

	label_songsDiff->setPosition(1200, 100);

	songsNameFrame->addChild(label_songsDiff);


	char labelScore[20];

	sprintf(labelScore, "%09d", score);

	auto label_score = Label::create(labelScore, "", 98);

	label_score->setAnchorPoint(Point::ONE);

	label_score->setPosition(Vec2(900, 150));

	scoreFrame->addChild(label_score);


	char labelCombo[20];

	sprintf(labelCombo, "%d", combo);

	auto label_combo = Label::create(labelCombo, "", 98);

	label_combo->setAnchorPoint(Vec2(0,0.5f));

	label_combo->setPosition(Vec2(550, 100));

	accFrame->addChild(label_combo);


	char labelAcc[20];

	sprintf(labelAcc, "%d%%", acc);

	auto label_acc = Label::create(labelAcc, "", 98);

	label_acc->setAnchorPoint(Vec2(0,0.5f));

	label_acc->setPosition(Vec2(1400, 100));

	accFrame->addChild(label_acc);


	char labelMiss[5];

	sprintf(labelMiss,"%d",miss);

	auto label_miss = Label::create(labelMiss,"",56);

	label_miss->setAnchorPoint(Point::ZERO);

	label_miss->setPosition(Vec2(1050,260));

	this->addChild(label_miss);


	char labelPoor[5];

	sprintf(labelPoor, "%d", poor);

	auto label_poor = Label::create(labelPoor, "", 56);

	label_poor->setAnchorPoint(Point::ZERO);

	label_poor->setPosition(Vec2(1050, 385));

	this->addChild(label_poor);


	char labelGood[5];

	sprintf(labelGood, "%d", good);

	auto label_good = Label::create(labelGood, "", 56);

	label_good->setAnchorPoint(Point::ZERO);

	label_good->setPosition(Vec2(1050, 510));

	this->addChild(label_good);


	char labelCool[5];

	sprintf(labelCool, "%d", cool);

	auto label_cool = Label::create(labelCool, "", 56);

	label_cool->setAnchorPoint(Point::ZERO);

	label_cool->setPosition(Vec2(1050, 635));

	this->addChild(label_cool);
    
    switch(grade)
    {
        case 1:
            evaluation = Sprite::create("img/GameOver/ranking-SSS@2x.png");
            break;
        case 2:
            evaluation = Sprite::create("img/GameOver/ranking-X@2x.png");
            break;
        case 3:
            evaluation = Sprite::create("img/GameOver/ranking-S@2x.png");
            break;
        case 4:
            evaluation = Sprite::create("img/GameOver/ranking-A@2x.png");
            break;
        case 5:
            evaluation = Sprite::create("img/GameOver/ranking-B@2x.png");
            break;
        case 6:
            evaluation = Sprite::create("img/GameOver/ranking-C@2x.png");
            break;
        case 7:
            evaluation = Sprite::create("img/GameOver/ranking-D@2x.png");
            break;
    }
    
    evaluation->setScale(0.6);
    
    evaluation->setPosition(Vec2(1400,470));
    
    this->addChild(evaluation);
    
    
    char coverFile[128];
    
    sprintf(coverFile,"songs/%d/cover.jpg",songId);
    
    Sprite* cover = Sprite::create(coverFile);
    
    cover->setOpacity(0);
    
    cover->runAction(FadeTo::create(0.5f,255));
    
    cover->setScale(600.0f/cover->getContentSize().height);
    
    cover->setPosition(400,538);
    
    this->addChild(cover);
    
    char str[256];
    sprintf(str, "{\"songId\":%d,\"diffName\":\"%s\",\"score\":%d,\"grade\":%d,\"combo\":%d,\"missCount\":%d,\"poorCount\":%d,\"goodCount\":%d,\"coolCount\":%d,\"acc\":%d}",songId,diffName,score,grade,combo,miss,poor,good,cool,acc);
    SocketIOClient::getInstance()->send("uploadScore", str);
    SocketIOClient::getInstance()->listen("uploadScoreRes", [=](SIOClient* client, std::string msg){
        rapidjson::Document doc;
        doc.Parse<0>(msg.c_str());
        
        int coin = doc["coin"].GetInt();
        
        this->getCoin(coin);
        
    });

}

void GameOver::getCoin(int coin)
{
    UserInfo::getInstance()->coin+=coin;
    
    auto root = Node::create();
    
    root->setPosition(960,1300);
    
    root->runAction(Sequence::create(DelayTime::create(1.0f),EaseSineOut::create(MoveBy::create(0.5f, Vec2(0,-400))),DelayTime::create(2.0f),EaseSineIn::create(MoveBy::create(0.5f, Vec2(0,400))), NULL));
    
    auto frame = Sprite::create("img/GameOver/coinFrame.png");
    
    root->addChild(frame);
    
    auto coinIcon = Sprite::create("img/GameOver/coin.png");
    
    coinIcon->setPosition(-100,0);
    
    root->addChild(coinIcon);
    
    char str[16];
    
    sprintf(str, "%dG",coin);
    
    auto coinLabel = Label::create(str,"Arial",64);
    
    coinLabel->setPosition(-20,0);
    
    coinLabel->setAnchorPoint(Vec2(0,0.5));
    
    root->addChild(coinLabel);
    
    this->addChild(root);
}

void GameOver::back()
{
    this->getParent()->addChild(SongsLayer::create());
    this->removeFromParent();
}

void GameOver::playAgain()
{
    this->getParent()->addChild(GameLayer::createWithId(this->songId,this->songName , this->diffName, 0));
    this->removeFromParent();
}
