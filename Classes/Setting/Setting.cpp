#include "Setting.h"
#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "LoginPanel.h"
#include "SettingData.h"
#include "PromptingFrame.h"


using namespace CocosDenshion;

bool Setting::init()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();


	bg = Sprite::create("img/setting/bg.png");

	bg->setPosition(visiblesize.width/2,visiblesize.height/2);

	this->addChild(bg);


	btn_back = MenuItemImage::create("img/setting/btn_back.png","img/setting/btn_back_p.png",CC_CALLBACK_0(Setting::backToMainMenu,this));

	btn_back->setPosition(btn_back->getContentSize().width/2,visiblesize.height-btn_back->getContentSize().height/2);

	auto ring = Sprite::create("img/selectsongs/ring.png");

	ring->setPosition(130, 100);

	ring->runAction(RepeatForever::create(RotateBy::create(4, 360)));

	btn_back->addChild(ring);


	btn_disableItem = MenuItemImage::create("img/setting/btn_disable.png", "img/setting/btn_disable_p.png", CC_CALLBACK_0(Setting::disableItemCallBack, this));

	btn_disableItem->setPosition(visiblesize.width*0.4,visiblesize.height*0.3);


	btn_aboutUs = MenuItemImage::create("img/setting/btn_aboutus.png","img/setting/btn_aboutus_p.png",CC_CALLBACK_0(Setting::aboutUs,this));

	btn_aboutUs->setPosition(visiblesize.width*0.7, visiblesize.height*0.3);


	btn_logout = MenuItemImage::create("img/setting/btn_logout.png","img/setting/btn_logout_p.png",CC_CALLBACK_0(Setting::logout,this));

	btn_logout->setPosition(visiblesize.width-btn_logout->getContentSize().width/2,btn_logout->getContentSize().height/2);


	Menu* menu = Menu::create(btn_back,btn_disableItem,btn_aboutUs,btn_logout,NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);


	label_musicVolume = Sprite::create("img/setting/musicvolume.png");

	label_musicVolume->setPosition(Vec2(1200,700));

	this->addChild(label_musicVolume);

	musicVolume = Slider::create();
	
	musicVolume->loadBarTexture("img/setting/slider.png");
	
	musicVolume->loadSlidBallTextures("img/setting/sliderthumb.png","img/setting/sliderthumb.png","");
	
	musicVolume->loadProgressBarTexture("img/setting/sliderprogress.png");

//	float effectPercent = SettingData::getInstance()->musicVolume;

	if (SettingData::getInstance()->musicVolume == 0.0f)
	{
		SettingData::getInstance()->musicVolume == 100.0f;
	}

	musicVolume->setPercent(SettingData::getInstance()->musicVolume);
	
	musicVolume->setPosition(Vec2(1200,700));

	musicVolume->addEventListener([=](Ref* pSender,Slider::EventType type){
	
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			float percent = musicVolume->getPercent();
			//SettingData::getInstance()->musicVolume = musicVolume->getPercent();
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent/100.0);
			SettingData::getInstance()->musicVolume = percent;
			//UserDefault::getInstance()->setFloatForKey("effectPercent",percent);
			SettingData::getInstance()->save();
		}

	});
	
	this->addChild(musicVolume);


	label_keyPressVolume = Sprite::create("img/setting/keypressvolume.png");

	label_keyPressVolume->setPosition(Vec2(1200, 600));

	this->addChild(label_keyPressVolume);

	keyPressVolume = Slider::create();

	keyPressVolume->loadBarTexture("img/setting/slider.png");

	keyPressVolume->loadSlidBallTextures("img/setting/sliderthumb.png", "img/setting/sliderthumb.png", "");

	keyPressVolume->loadProgressBarTexture("img/setting/sliderprogress.png");

//	float volumePercent = UserDefault::getInstance()->getFloatForKey("volumePercent");

	if (SettingData::getInstance()->effectVolume == 0.0f)
	{
		SettingData::getInstance()->effectVolume == 100.0f;
	}

	keyPressVolume->setPercent(SettingData::getInstance()->effectVolume);

	keyPressVolume->setPosition(Vec2(1200, 600));

	keyPressVolume->addEventListener([=](Ref* pSender, Slider::EventType type){

		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			int percent = keyPressVolume->getPercent();

			SimpleAudioEngine::getInstance()->setEffectsVolume(float(percent) / 100);

			SettingData::getInstance()->effectVolume = percent;

			SettingData::getInstance()->save();

			//UserDefault::getInstance()->setFloatForKey("volumePercent", percent);
		}

	});

	this->addChild(keyPressVolume);

	btnIsSelected = Sprite::create("img/setting/btn_disable_p.png");
	btnIsSelected->setPosition(btn_disableItem->getContentSize().width / 2, btn_disableItem->getContentSize().height / 2);
	btn_disableItem->addChild(btnIsSelected);
//	btnIsSelected->setVisible(false);
	if (SettingData::getInstance()->disableItem)
	{
		btnIsSelected->setVisible(true);
	}
	else
	{
		btnIsSelected->setVisible(false);
	}
	return true;
}

void Setting::backToMainMenu()
{
	this->getParent()->addChild(MainMenuLayer::create());

	this->removeFromParent();
}

void Setting::disableItemCallBack()
{
	
	if (SettingData::getInstance()->disableItem)
	{
		SettingData::getInstance()->disableItem = false;
		
		btnIsSelected->setVisible(false);

		SettingData::getInstance()->save();
	}
	else
	{
		SettingData::getInstance()->disableItem = true;
		
		btnIsSelected->setVisible(true);

		SettingData::getInstance()->save();
	}
}

void Setting::aboutUs()
{
	auto promptingFrame = PromptingFrame::createWithId(2);

	this->addChild(promptingFrame);
}

void Setting::logout()
{
	this->getParent()->addChild(LoginPanel::create());

	this->removeFromParent();
}
