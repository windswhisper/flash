#include "SongsInfo.h"

SongsInfo* SongsInfo::getInstance()
{
    if(_songsInfo==NULL)
    {
        _songsInfo = new SongsInfo();
        _songsInfo->load();
    }
    return _songsInfo;
}

void SongsInfo::load()
{
    for(int i=0;i<5;i++)
    {
        this->addSong(i, "1", "1", "1");
    }
}

void SongsInfo::addSong(int id,const char *name,const char *length,const char *artist)
{
    auto song = new Song();
    
    song->id = id;
    
    strcpy(song->name, name);
    
    strcpy(song->length, length);
    
    strcpy(song->artist, artist);

    this->songs.push_back(song);
}
