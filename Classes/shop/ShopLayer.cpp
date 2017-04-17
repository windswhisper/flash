#include "ShopLayer.h"
#include "SongsExtraction.h"
#include "MainMenuLayer.h"

ShopLayer::ShopLayer()
{
}
ShopLayer::~ShopLayer()
{
}
bool ShopLayer::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();
	
	shop_bg = Sprite::create("img/shop/shop_bg.png");

	shop_bg->setPosition(Vec2(visiblesize.width/2,visiblesize.height/2));

	this->addChild(shop_bg);

	btn_mainmenu = MenuItemImage::create("img/shop/btn_mainmenu.png", "img/shop/btn_mainmenu_p.png", CC_CALLBACK_0(ShopLayer::backToMenu, this));

	btn_mainmenu->setPosition(250, 973 + 300);

	btn_mainmenu->runAction(Sequence::create(DelayTime::create(0.3f), (EaseSineOut::create(MoveBy::create(1, Vec2(0, -300)))), NULL));

	auto ringL = Sprite::create("img/selectsongs/ring.png");

	ringL->setPosition(130, 98);

	ringL->runAction(RepeatForever::create(RotateBy::create(4, 360)));

	btn_mainmenu->addChild(ringL);

//	this->addChild(btn_mainmenu);

	btn_skin = MenuItemImage::create("img/shop/skin.png", "img/shop/skin.png", CC_CALLBACK_0(ShopLayer::skinSelect, this));

	btn_skin->setPosition(visiblesize.width - btn_skin->getContentSize().width/2 + 8, visiblesize.height - btn_mainmenu->getContentSize().height + btn_skin->getContentSize().height/2 - 8);

	btn_duel = MenuItemImage::create("img/shop/duel.png", "img/shop/duel.png", CC_CALLBACK_0(ShopLayer::duelSelect, this));

	btn_duel->setPosition(visiblesize.width - btn_skin->getContentSize().width / 2 * 3 + 32, visiblesize.height - btn_mainmenu->getContentSize().height + btn_skin->getContentSize().height / 2 - 8);
	
	btn_item = MenuItemImage::create("img/shop/item.png", "img/shop/item.png", CC_CALLBACK_0(ShopLayer::itemSelect, this));

	btn_item->setPosition(visiblesize.width - btn_skin->getContentSize().width / 2 * 5 + 64, visiblesize.height - btn_mainmenu->getContentSize().height + btn_skin->getContentSize().height / 2 - 8);

	btn_skill = MenuItemImage::create("img/shop/skill.png", "img/shop/skill.png", CC_CALLBACK_0(ShopLayer::skillSelect, this));

	btn_skill->setPosition(visiblesize.width - btn_skin->getContentSize().width / 2 * 7 + 96, visiblesize.height - btn_mainmenu->getContentSize().height + btn_skin->getContentSize().height / 2 - 8);

	btn_songspackage = MenuItemImage::create("img/shop/songspackage.png", "img/shop/songspackage.png", CC_CALLBACK_0(ShopLayer::songsPackageSelect, this));

	btn_songspackage->setPosition(visiblesize.width - btn_skin->getContentSize().width / 2 * 9 + 128, visiblesize.height - btn_mainmenu->getContentSize().height + btn_skin->getContentSize().height / 2 - 8);

	btn_songsextraction = MenuItemImage::create("img/shop/selectsong.png", "img/shop/selectsong.png", CC_CALLBACK_0(ShopLayer::songsSelect, this));

	btn_songsextraction->setPosition(visiblesize.width - btn_skin->getContentSize().width / 2 * 11 + 160, visiblesize.height - btn_mainmenu->getContentSize().height + btn_skin->getContentSize().height / 2 - 8);

	Menu* menu = Menu::create(btn_mainmenu, btn_skin, btn_duel, btn_item, btn_skill, btn_songspackage, btn_songsextraction, NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	auto line = Sprite::create("img/shop/line.png");

	line->setPosition(1210, visiblesize.height - btn_mainmenu->getContentSize().height);

	this->addChild(line);

	auto money = Sprite::create("img/shop/money.png");

	money->setPosition(240,790);

	this->addChild(money);

//	tabSelect = Sprite::create("img/shop/tab_select.png");

//	tabSelect->setPosition(btn_skin->getContentSize().width / 2, btn_skin->getContentSize().height / 2);

	node = Node::create();

	this->addChild(node);

	button = btn_songsextraction;

	button->addChild(this->addPressSprite());

	songsExtraction = SongsExtraction::create();

	songsExtraction->setPosition(200, -40);

	node->addChild(songsExtraction);

	return true;
}

Sprite* ShopLayer::addPressSprite()
{
	tabSelect = Sprite::create("img/shop/tab_select.png");

	tabSelect->setPosition(btn_skin->getContentSize().width / 2, btn_skin->getContentSize().height / 2);

	return tabSelect;
}

void ShopLayer::songsSelect()
{
	this->close();

	node = Node::create();

	button = btn_songsextraction;

	button->addChild(this->addPressSprite());

	songsExtraction = SongsExtraction::create();

	songsExtraction->setPosition(200,-40);

	node->addChild(songsExtraction);

	this->addChild(node);
}

void ShopLayer::songsPackageSelect()
{
	this->close();

	node = Node::create();

	button = btn_songspackage;

	button->addChild(this->addPressSprite());

	songsPackage = SongsPackage::create();

	songsPackage->setPosition(-300,-300);

	node->addChild(songsPackage);

	this->addChild(node);
}

void ShopLayer::skillSelect()
{
	this->close();

	button = btn_skill;

	button->addChild(this->addPressSprite());

	node = Node::create();

	skill = Skill::create();

	skill->setPosition(-300, -300);

	node->addChild(skill);

	this->addChild(node);
}

void ShopLayer::itemSelect()
{
	this->close();

	button = btn_item;

	button->addChild(this->addPressSprite());
}

void ShopLayer::duelSelect()
{
	this->close();

	button = btn_duel;

	button->addChild(this->addPressSprite());
}

void ShopLayer::skinSelect()
{
	this->close();

	button = btn_skin;

	button->addChild(this->addPressSprite());
}

void ShopLayer::close()
{
	this->removeChild(node);

	button->removeChild(tabSelect);
}

void ShopLayer::backToMenu()
{
	this->removeAllChildren();

	this->getParent()->addChild(MainMenuLayer::create());
}