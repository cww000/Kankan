#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include "relationalbroker.h"
#include "comment.h"
#include <mutex>
#include <string>
class CommentBroker : public RelationalBroker
{
public:
    ~CommentBroker();
    static CommentBroker* getInstance();
    static void flush();
    std::shared_ptr<Comment> getComment(const std::string& id);
    std::shared_ptr<Comment> retrieveComment(const std::string& id);
    //将新增的评论添加到新的净缓存
    void addComment(const std::string& id, const Comment& comment);

    //删除评论
    void deleteComment(const std::string& id, const Comment& comment);

private:
    CommentBroker();
    static CommentBroker* m_commentBroker;
    static std::mutex m_mutex;
    static std::unordered_map<std::string, Comment> _newClean;  //新的净缓存
    static std::unordered_map<std::string, Comment> _newDirty;  //新的脏缓存
    static std::unordered_map<std::string, Comment> _newDelete; //新的删除缓存
    static std::unordered_map<std::string, Comment> _oldClean;  //旧的净缓存
    static std::unordered_map<std::string, Comment> _oldDirty;  //旧的脏缓存
    static std::unordered_map<std::string, Comment> _oldDelete; //旧的删除缓存

    static void cacheFlush();   //将数据写入数据库
    static void cacheDel();  //删除数据库中的数据
    static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<Comment> inCache(std::string id);   //判断是否在缓存中
    int judgeFrom(const std::string& id);  //判断要删除的数据是在哪一个缓存
};

#endif // COMMENTBROKER_H
