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
    //添加到净缓存
    void addVideo(const std::string& id, const Video& video);
    //添加到删除缓存
    void deleteVideo(const std::string& id, const Video& video);

    //检索缓存以及数据库，返回video对象
    //id：稿件id

private:
    static VideoBroker* m_videoBroker;
    static std::mutex m_mutex;
    static std::unordered_map<std::string, Video> _newClean;  //新的净缓存
    static std::unordered_map<std::string, Video> _newDirty;  //新的脏缓存
    static std::unordered_map<std::string, Video> _newDelete; //新的删除缓存
    static std::unordered_map<std::string, Video> _oldClean;  //旧的净缓存
    static std::unordered_map<std::string, Video> _oldDirty;  //旧的脏缓存
    static std::unordered_map<std::string, Video> _oldDelete; //旧的删除缓存

    VideoBroker();
    static void cacheFlush();   //将数据写入数据库
    static void cacheDel();  //删除数据库中的数据
    static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<Video> inCache(std::string id);   //判断是否在缓存中
    int judgeFromForDel(const std::string& id);  //判断要删除的数据是在哪一个缓存
};

#endif // VIDEOBROKER_H
