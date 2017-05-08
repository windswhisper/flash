#ifndef __SETTING_DATA_H__
#define __SETTING_DATA_H__

#include "cocos2d.h"

USING_NS_CC;

class SettingData
{
public:
    static SettingData* getInstance();
    
    void load();
    
    void save();
    
    float musicVolume;
    
    float effectVolume;
    
    bool disableItem;
    
    bool itemSwitch[8];
};
static SettingData* _settingData;

#endif
