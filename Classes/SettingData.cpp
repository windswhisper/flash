#include "SettingData.h"

SettingData* SettingData::getInstance()
{
    if(_settingData==NULL)
    {
        _settingData = new SettingData();
        _settingData->load();
    }
    return _settingData;
}

void SettingData::load()
{
    musicVolume = UserDefault::getInstance()->getFloatForKey("musicVolume",80);
    
    effectVolume = UserDefault::getInstance()->getFloatForKey("effectVolume",60);
    
    disableItem = UserDefault::getInstance()->getBoolForKey("disableItem",false);
    
    for(int i=0;i<8;i++)
    {
        char key[20];
        
        sprintf(key, "itemSwitch%d",i);
        
        itemSwitch[i] = UserDefault::getInstance()->getBoolForKey(key,false);
    }
}

void SettingData::save()
{
    UserDefault::getInstance()->setFloatForKey("musicVolume",this->musicVolume);
    
    UserDefault::getInstance()->setFloatForKey("effectVolume",this->effectVolume);
    
    UserDefault::getInstance()->setBoolForKey("disableItem",this->disableItem);
    
    for(int i=0;i<8;i++)
    {
        char key[20];
        
        sprintf(key, "itemSwitch%d",i);
        
        UserDefault::getInstance()->setBoolForKey(key,this->itemSwitch[i]);
    }
}
