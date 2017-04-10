#include "SongsInfo.h"
#include "SocketIOClient.h"

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
    SocketIOClient::getInstance()->send("songsList", "");
    SocketIOClient::getInstance()->lock();
    SocketIOClient::getInstance()->listen("songsListRes", [=](SIOClient* client, std::string msg){
        rapidjson::Document doc;
        doc.Parse<0>(msg.c_str());
        
        for(int i=0;i<doc.Size();i++)
        {
            this->addSong(doc[i]["songId"].GetInt(), doc[i]["name"].GetString(), "", "");
        }
        
        SocketIOClient::getInstance()->unlock();
    });

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
