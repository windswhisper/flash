#ifndef __SONGS_INFO_H__
#define __SONGS_INFO_H__

#include "cocos2d.h"

#include <vector>

using namespace std ;
USING_NS_CC;

struct Diffcult
{
    char name[32];
    int level;
};

struct Song
{
    int id;
    char name[64];
    char length[32];
    char artist[64];
    vector<Diffcult*> diffs;
};

class SongsInfo
{
public:
    static SongsInfo* getInstance();
    
    void load();
    
    void addSong(int id,const char* name,const char* length,const char* artist,const char* diffName,int diffLevel);
    
    vector<Song*> songs;
    
    Song* getInfoById(int id);
};
static SongsInfo* _songsInfo;

#endif
