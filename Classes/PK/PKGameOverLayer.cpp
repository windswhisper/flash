#include "PKGameOverLayer.h"

bool PKGameOverLayer::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();


	PK_bg = Sprite::create("img/PK/PK_bg.png");

	PK_bg->setPosition(visiblesize.width/2,visiblesize.height/2);

	this->addChild(PK_bg);


	songsNameFrame = Sprite::create("img/selectsongs/info_frame.png");

	songsNameFrame->setPosition(visiblesize.width/2,visiblesize.height - songsNameFrame->getContentSize().height/2);

	this->addChild(songsNameFrame);


	winnerNameFrame = Sprite::create("img/PK/PK_playerNameFrame.png");

	winnerNameFrame->setPosition(Vec2(650,800));

	this->addChild(winnerNameFrame);


	loserNameFrame = Sprite::create("img/PK/PK_playerNameFrame.png");

	loserNameFrame->setPosition(Vec2(1250, 700));

	this->addChild(loserNameFrame);


	PK_vs = Sprite::create("img/PK/vs.png");

	PK_vs->setPosition(visiblesize.width/2,750);

	this->addChild(PK_vs);


	winnerGrade = Sprite::create("img/PK/PK_grade.png");

	winnerGrade->setPosition(650,400);

	this->addChild(winnerGrade);


	loserGrade = Sprite::create("img/PK/PK_grade.png");

	loserGrade->setPosition(1250, 300);

	this->addChild(loserGrade);


	winner = Sprite::create("img/PK/winner.png");

	winner->setPosition(250,900);

	this->addChild(winner);


	loser = Sprite::create("img/PK/winner.png");

	loser->setPosition(1750, 850);

	this->addChild(loser);


	return true;
}

void PKGameOverLayer::setData(char* songName, char* songDiff, char* winnerName, char* loserName, int winnerScore, int winnerCombo, int winnerAcc, int loserScore, int loserCombo, int loserAcc)
{
	auto label_songName = Label::create(songName,"",72);

	label_songName->setPosition(30,20);

	songsNameFrame->addChild(label_songName);


	auto label_songDiff = Label::create(songDiff, "", 72);

	label_songDiff->setPosition(30, 10);

	songsNameFrame->addChild(label_songDiff);


	auto label_winnerName = Label::create(winnerName,"",72);

	label_winnerName->setPosition(winnerNameFrame->getContentSize().width/2,winnerNameFrame->getContentSize().height/2);

	winnerNameFrame->addChild(label_winnerName);


	auto label_loserName = Label::create(loserName, "", 72);

	label_loserName->setPosition(loserNameFrame->getContentSize().width / 2, loserNameFrame->getContentSize().height / 2);

	loserNameFrame->addChild(label_loserName);


//	char winner_score[128];

	sprintf(winner_score,"%d",winnerScore);

	auto label_winnerScore = Label::create(winner_score,"", 72);

	label_winnerScore->setAnchorPoint(Point::ZERO);

	label_winnerScore->setPosition(150,100);

	winnerGrade->addChild(label_winnerScore);
}