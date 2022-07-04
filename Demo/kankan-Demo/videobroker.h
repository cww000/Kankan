#ifndef VIDEOBROKER_H
#define VIDEOBROKER_H

#include "relationalbroker.h"
#include "video.h"

class VideoBroker : public RelationalBroker
{
public:
    ~VideoBroker();
    static VideoBroker* getInstance();

    Video* getVideo(std::string id);
    //检索缓存以及数据库，返回video对象
    //id：稿件id

private:
    VideoBroker();
    static VideoBroker* m_videoBroker;
};

#endif // VIDEOBROKER_H
