#ifndef __USER_INFO_H__
#define __USER_INFO_H__

#include "cocos2d.h"

USING_NS_CC;

class UserInfo
{
public:
    static UserInfo* getInstance();
    
    void load();
    
    int userId;
    
    char username[32];
    
    int coin;
    
    int item[3];

    int skill[3];
    
};
static UserInfo* _userInfo;

#endif
