#include "SongsListView.h"

#include "SongsInfo.h"

bool SongsListView::init()
{
    auto songs = SongsInfo::getInstance()->songs;

    for(int i=0;i<songs.size();i++)
    {
        Sprite* item = Sprite::create("img/selectsongs/btn_song.png");
        
        item->setPosition(0,-i*200);
        
        this->addChild(item);
    }
    
    return true;
}
