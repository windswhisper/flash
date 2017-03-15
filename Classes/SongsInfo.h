#ifndef __SONGS_INFO_H__
#define __SONGS_INFO_H__

#include "cocos2d.h"

#include <vector>

using namespace std ;
USING_NS_CC;

struct Song
{
    int id;
    char name[64];
    char length[32];
    char artist[64];
};

class SongsInfo
{
public:
    static SongsInfo* getInstance();
    
    void load();
    
    void addSong(int id,const char* name,const char* length,const char* artist);
    
    vector<Song*> songs;
    
    
};
static SongsInfo* _songsInfo;

#endif
