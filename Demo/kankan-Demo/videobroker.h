#ifndef VIDEOBROKER_H
#define VIDEOBROKER_H

#include "relationalbroker.h"
#include "video.h"
#include <mutex>
class VideoBroker : public RelationalBroker
{
public:
    ~VideoBroker();
    static VideoBroker* getInstance();
    static void flush();
    std::shared_ptr<Video> getVideo(const std::string& id);
    std::shared_ptr<Video> retrieveVideo(const std::string& id);

    //检索缓存以及数据库，返回video对象
    //id：稿件id

private:
    VideoBroker();
    static VideoBroker* m_videoBroker;
    static std::mutex m_mutex;
    static std::unordered_map<std::string, Video> _newClean;  //新的净缓存
    static std::unordered_map<std::string, Video> _newDirty;  //新的脏缓存
    static std::unordered_map<std::string, Video> _newDelete; //新的删除缓存
    static std::unordered_map<std::string, Video> _oldClean;  //旧的净缓存
    static std::unordered_map<std::string, Video> _oldDirty;  //旧的脏缓存
    static std::unordered_map<std::string, Video> _oldDelete; //旧的删除缓存

    static void cacheFlush();   //将数据写入数据库
    static void cacheDel();  //删除数据库中的数据
    static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<Video> inCache(std::string id);   //判断是否在缓存中
};

#endif // VIDEOBROKER_H
