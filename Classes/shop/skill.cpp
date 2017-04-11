#include "skill.h"

bool Skill::init()
{
	scrollView = ScrollView::create();

	scrollView->setContentSize(Size(1350, 600));

	scrollView->setDirection(ScrollView::Direction::VERTICAL);

	scrollView->setBounceEnabled(true);

	scrollView->setInnerContainerSize(scrollView->getContentSize());

	scrollView->setPosition(Vec2(300, 400));

	this->addChild(scrollView);

	this->setSkill();

	skillInfo = ShopItemInfo::createWithInfo(skillID[0]);

	skillInfo->setPosition(1000, 200);

	this->addChild(skillInfo);

	return true;
}

void Skill::setSkill()
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

		skill[i]->addTouchEventListener(CC_CALLBACK_0(Skill::skillSelect, this,skillID[i]));

		item->addChild(skill[i]);
	}

	scrollView->addChild(item);
}

void Skill::skillSelect(char* skillId)
{
	this->removeChild(skillInfo);

	//	songspackageinfo = SongsPackageInfo::create();
	skillInfo = ShopItemInfo::createWithInfo(skillId);

	skillInfo->setPosition(1000, 200);

	this->addChild(skillInfo);
}