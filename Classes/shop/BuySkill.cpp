#include "BuySkill.h"

bool BuySkill::init()
{
	scrollView = ScrollView::create();

	scrollView->setContentSize(Size(1350, 600));

	scrollView->setDirection(ScrollView::Direction::VERTICAL);

	scrollView->setBounceEnabled(true);

	scrollView->setInnerContainerSize(scrollView->getContentSize());

	scrollView->setPosition(Vec2(300, 400));

	this->addChild(scrollView);

	this->setSkill();

    skillInfo = nullptr;
    
    auto bg = Sprite::create("img/shop/songspackage/songspackageinfobg.png");
    
    bg->setPosition(1930,733);
    
    this->addChild(bg);
    
	return true;
}

void BuySkill::setSkill()
{
	Layout* item = Layout::create();

	item->setContentSize(Size(300, 300));

	item->setPosition(Vec2(0, 0));

	for (int i = 0; i < 3; ++i)
	{
		sprintf(skillID[i], "skill\%d", i + 1);

		skill[i] = Button::create("img/shop/songspackage/item.png", "img/shop/songspackage/item_p.png");

		skill[i]->setContentSize(Size(300, 300));

		skill[i]->setPosition(Vec2(200 + 500 * i, 400 ));

		skill[i]->addTouchEventListener(CC_CALLBACK_0(BuySkill::skillSelect, this,skillID[i]));

		item->addChild(skill[i]);
	}

	scrollView->addChild(item);
}

void BuySkill::skillSelect(char* skillId)
{
    if(skillInfo!=nullptr)
        this->removeChild(skillInfo);

	//	songspackageinfo = SongsPackageInfo::create();
	skillInfo = ShopItemInfo::createWithInfo(skillId,"",10,nullptr);

	skillInfo->setPosition(1930,733);

	this->addChild(skillInfo);
}
