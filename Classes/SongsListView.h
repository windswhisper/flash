#ifndef __SONGS_LIST_VIEW_H__
#define __SONGS_LIST_VIEW_H__

#include "cocos2d.h"

USING_NS_CC;


class SongsListView : public Node
{
public:
    virtual bool init();
    
    CREATE_FUNC(SongsListView);

    Vector<Sprite*> itemSong;
    
};

#endif
