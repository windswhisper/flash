#include "ShopConfig.h"
#include "UserInfo.h"
#include "ShopLayer.h"
#include "PromptingFrame.h"

ShopConfig* ShopConfig::getInstance()
{
    if(_shopConfig==NULL)
    {
        _shopConfig = new ShopConfig();
        _shopConfig->load();
    }
    return _shopConfig;
}

void ShopConfig::load()
{
    std::string str = FileUtils::getInstance()->getStringFromFile("s");
    
    doc.Parse<0>(str.c_str());
}

ItemInfo ShopConfig::getInfo(char* id)
{
    ItemInfo info;
    
    strcpy(info.name , doc[id]["title"].GetString());
    
    strcpy(info.intro , doc[id]["info"].GetString());
    
    info.price = doc[id]["price"].GetInt();

    return info;
}

bool ShopConfig::checkCoin(int price)
{
    if(UserInfo::getInstance()->coin<price)
    {
        ShopLayer::getInstance()->addChild( PromptingFrame::createWithId(2));
        return false;
    }
    else{
        UserInfo::getInstance()->coin-=price;
        ShopLayer::getInstance()->updateMoney();
        //ShopLayer::getInstance()->addChild( PromptingFrame::createWithId(6));
        return true;
    }
}
