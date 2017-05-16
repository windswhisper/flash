#include "PKGameOverLayer.h"
#include "PKSelectDiff.h"

bool PKGameOverLayer::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();


	PK_bg = Sprite::create("img/PK/PK_bg.png");

	PK_bg->setPosition(visiblesize.width/2,visiblesize.height/2);

	this->addChild(PK_bg);


	songsNameFrame = Sprite::create("img/selectsongs/info_frame.png");

	songsNameFrame->setPosition(visiblesize.width/2,visiblesize.height - songsNameFrame->getContentSize().height/2 + 210);

	songsNameFrame->runAction(EaseSineIn::create(MoveBy::create(1.0f,Vec2(2,-200))));

	this->addChild(songsNameFrame);


	winnerNameFrame = Sprite::create("img/PK/PK_playerNameFrame.png");

	winnerNameFrame->setPosition(Vec2(500 - 1000,680 - 30));

	this->addChild(winnerNameFrame);


	loserNameFrame = Sprite::create("img/PK/PK_playerNameFrame.png");

	loserNameFrame->setPosition(Vec2(1415 + 1000, 620 + 30));

	this->addChild(loserNameFrame);
    
    winnerNameFrame->runAction(EaseSineIn::create(MoveBy::create(0.5f, Vec2(1000, 0))));
    loserNameFrame->runAction(EaseSineIn::create(MoveBy::create(0.5f, Vec2(-1000, 0))));

	PK_vs = Sprite::create("img/PK/vs.png");

	PK_vs->setPosition(visiblesize.width/2,650);

	PK_vs->setOpacity(0);

	PK_vs->runAction(Sequence::create(FadeIn::create(1),Repeat::create(Sequence::create(ScaleTo::create(0.5f,1.5f),ScaleTo::create(0.5f,1),NULL),4),NULL));

	this->addChild(PK_vs);


	myGradeFrame = Sprite::create("img/PK/PK_grade.png");

	myGradeFrame->setPosition(Vec2(455,280 - 520));

	this->addChild(myGradeFrame);


	opnGradeFrame = Sprite::create("img/PK/PK_grade.png");

	opnGradeFrame->setPosition(Vec2(1460, 280 - 520));

	this->addChild(opnGradeFrame);
    
    myGradeFrame->runAction(MoveBy::create(1,Vec2(0,520)));
    opnGradeFrame->runAction( MoveBy::create(1, Vec2(0, 520)));

	winner = Sprite::create("img/PK/winner.png");

	winner->setPosition(Vec2(140,260));

	winner->setVisible(false);

	winnerNameFrame->addChild(winner);


	loser = Sprite::create("img/PK/loser.png");

	loser->setPosition(Vec2(720, 260));

	loser->setVisible(false);

	loserNameFrame->addChild(loser);


	back = Button::create("img/PK/btn_back.png","img/PK/btn_back_p.png");

	back->setPosition(Vec2(back->getContentSize().width/2,980 + 200));

	back->addTouchEventListener(CC_CALLBACK_0(PKGameOverLayer::backToPK,this));

	back->runAction(EaseSineInOut::create(MoveBy::create(1.0f,Vec2(0,-200))));

	this->addChild(back);


	auto ring = Sprite::create("img/selectsongs/ring.png");

	ring->setPosition(130, 100);

	ring->runAction(RepeatForever::create(RotateBy::create(4, 360)));

	back->addChild(ring);


	return true;
}

void PKGameOverLayer::setData(char* songName,char* songDiff,char* myName,const char* opnName,int myScore,int myCombo,int myAcc,int opnScore,int opnCombo,int opnAcc,int myGrade,int opnGrade)
{
	auto label_songName = Label::create(songName,"Arial",72);

	label_songName->setPosition(Vec2(songsNameFrame->getContentSize().width/2, 160));

	songsNameFrame->addChild(label_songName);


	auto label_songDiff = Label::create(songDiff, "Arial", 64);

	label_songDiff->setPosition(Vec2(songsNameFrame->getContentSize().width / 2, 80));

	songsNameFrame->addChild(label_songDiff);


	auto label_winnerName = Label::create(myName,"Arial",96);

	label_winnerName->setPosition(winnerNameFrame->getContentSize().width/2,winnerNameFrame->getContentSize().height/2);

	winnerNameFrame->addChild(label_winnerName);


	auto label_loserName = Label::create(opnName, "Arial", 96);

	label_loserName->setPosition(loserNameFrame->getContentSize().width / 2, loserNameFrame->getContentSize().height / 2);

	loserNameFrame->addChild(label_loserName);

	this->setGrade(myScore,myCombo,myAcc,true,myGrade);

	this->setGrade(opnScore, opnCombo, opnAcc,false,opnGrade);
    
    if(myScore>opnScore)
    {
        winnerNameFrame->runAction(Sequence::create( MoveBy::create(1, Vec2(0, 30)), CallFunc::create([=](){winner->setVisible(true); }), NULL));
        loserNameFrame->runAction(Sequence::create( MoveBy::create(1, Vec2(0, -30)), CallFunc::create([=](){loser->setVisible(true); }), NULL));
        
        myGradeFrame->runAction(MoveBy::create(1,Vec2(0,30)));
        opnGradeFrame->runAction( MoveBy::create(1, Vec2(0, -30)));
    }
    else{
        winner->setTexture("img/PK/loser.png");
        loser->setTexture("img/PK/winner.png");
        loserNameFrame->runAction(Sequence::create( MoveBy::create(1, Vec2(0, 30)), CallFunc::create([=](){winner->setVisible(true); }), NULL));
        winnerNameFrame->runAction(Sequence::create( MoveBy::create(1, Vec2(0, -30)), CallFunc::create([=](){loser->setVisible(true); }), NULL));
        
        opnGradeFrame->runAction(MoveBy::create(1,Vec2(0,30)));
        myGradeFrame->runAction( MoveBy::create(1, Vec2(0, -30)));
    }

}


void PKGameOverLayer::setGrade(int score, int combo, int acc,bool isMine,int playerGrade)
{
	char playerScore[16];

	sprintf(playerScore, "%d", score);

	auto label_score = Label::create(playerScore, "Arial", 72);

	label_score->setAnchorPoint(Point::ZERO);

	label_score->setPosition(Vec2(400, 370));


	char playerCombo[8];

	sprintf(playerCombo, "%d", combo);

	auto label_combo = Label::create(playerCombo, "Arial", 72);

	label_combo->setAnchorPoint(Point::ZERO);

	label_combo->setPosition(Vec2(320, 205));


	char playerAcc[8];

	sprintf(playerAcc, "%d%%", acc);

	auto label_acc = Label::create(playerAcc, "Arial", 72);

	label_acc->setAnchorPoint(Point::ZERO);

	label_acc->setPosition(Vec2(260, 45));


	switch (playerGrade)
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

	evaluation->setScale(0.35);

	evaluation->setPosition(Vec2(585, 185));


	if (isMine)
	{
		myGradeFrame->addChild(label_score);
		myGradeFrame->addChild(label_combo);
		myGradeFrame->addChild(label_acc);
		myGradeFrame->addChild(evaluation);
	}
	else
	{
		opnGradeFrame->addChild(label_score);
		opnGradeFrame->addChild(label_combo);
		opnGradeFrame->addChild(label_acc);
		opnGradeFrame->addChild(evaluation);
	}		
}

void PKGameOverLayer::backToPK()
{
	this->close(CallFunc::create([=]()
	{
		this->getParent()->addChild(PKSelectDiff::create());
	}));
}

void PKGameOverLayer::close(CallFunc* callfunc)
{
	this->getEventDispatcher()->removeEventListenersForTarget(this, true);


	songsNameFrame->runAction(MoveBy::create(1,Vec2(0,200)));

	winnerNameFrame->runAction(MoveBy::create(1, Vec2(-1000, 0)));

	winner->runAction(MoveBy::create(1, Vec2(-1000, 0)));

	loserNameFrame->runAction(MoveBy::create(1, Vec2(1000, 0)));

	loser->runAction(MoveBy::create(1, Vec2(1000, 0)));

	PK_vs->runAction(FadeOut::create(1));

	myGradeFrame->runAction(MoveBy::create(1,Vec2(0,-550)));

	back->runAction(MoveBy::create(1,Vec2(0,200)));

	opnGradeFrame->runAction(Sequence::create(MoveBy::create(1, Vec2(0, -490)), callfunc, CallFunc::create(CC_CALLBACK_0(PKGameOverLayer::removeFromParent, this)), NULL));
}
