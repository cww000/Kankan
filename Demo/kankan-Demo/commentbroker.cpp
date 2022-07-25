#include "commentbroker.h"
#include <iostream>

CommentBroker* CommentBroker::m_commentBroker = nullptr;
std::mutex CommentBroker::m_mutex = {};
std::unordered_map<std::string, Comment> CommentBroker::_newClean = {};
//std::unordered_map<std::string, Comment> CommentBroker::_newDirty = {};
std::unordered_map<std::string, Comment> CommentBroker::_newDelete = {};
std::unordered_map<std::string, Comment> CommentBroker::_oldClean = {};
//std::unordered_map<std::string, Comment> CommentBroker::_oldDirty = {};
std::unordered_map<std::string, Comment> CommentBroker::_oldDelete = {};

CommentBroker::~CommentBroker()
{
    flush();
}

CommentBroker *CommentBroker::getInstance()
{
    if (m_commentBroker == nullptr)
        m_commentBroker = new CommentBroker();
    return m_commentBroker;
}

void CommentBroker::flush()
{
    cacheFlush(); //向数据库中插入数据
    cacheDel();   //删除数据库中数据
//    cacheUpdate();  //更新数据库中数据
}

std::shared_ptr<Comment> CommentBroker::getComment(const std::string &id)
{
    //判断是否存在缓存中
    std::shared_ptr<Comment> comment = inCache(id);
    if (comment == nullptr) {
        return retrieveComment(id);   //如果数据不在缓存中，则追踪数据库
    }

    return comment;

}

std::shared_ptr<Comment> CommentBroker::retrieveComment(const std::string &id)
{
    //检索数据库，创建对象
    std::string sql = "select * from comment where id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> parameters;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());
        parameters.push_back(res->getString(2).c_str());
        parameters.push_back(res->getString(3).c_str());
        parameters.push_back(res->getString(4).c_str());
    }

    Comment com(parameters[0], parameters[1], parameters[2], parameters[3]);
 //   std::cout << "Comment对象实例化成功" << std::endl;
     _oldClean.insert({id, com});

     return std::make_shared<Comment>(_oldClean.at(id));
}

void CommentBroker::addComment(const std::string& id,const Comment &comment)
{
    _newClean.insert({id,comment});
}

void CommentBroker::deleteComment(const std::string &id, const Comment &comment)
{
    int n = judgeFromForDel(id);
    if (n == 0) {
        //如果该评论对象是在新的净缓存中
        //将该评论对象从新的净缓存移动到新的删除缓存
         _newClean.erase(id);
        _newDelete.insert({id, comment});
    } /*else if (n == 1){
        //如果该评论对象是在新的脏缓存中
        //将该评论对象从新的脏缓存移动到新的删除缓存
         _newDirty.erase(id);
        _newDelete.insert({id, comment});
    }*/ else if (n == 2) {
          //如果该评论对象是在旧的净缓存中
          //将该评论对象从旧的净缓存移动到旧的删除缓存
        _oldClean.erase(id);
        _oldDelete.insert({id, comment});
    }/* else {
        //如果该评论对象是在旧的脏缓存中
        //将该评论对象从旧的脏缓存移动到旧的删除缓存
        _oldDirty.erase(id);
        _oldDelete.insert({id, comment});
    }*/
}

void CommentBroker::cacheFlush()
{
    if (!_newClean.empty() /*|| !_newDirty.empty()*/) {
        std::string sql = "insert into comment values";
        for(auto iter = _newClean.begin(); iter != _newClean.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "('" + iter->first+ "','" + iter->second.getText() + "','" + iter->second.videoId() + "','" + iter->second.user_id() + "'),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newClean.erase(iter++);
        }

//        for(auto it = _newDirty.begin(); it != _newDirty.end();){

//            //应该保证当进行插入时，数据是不可以被其他线程所更改的
//            std::lock_guard<std::mutex> lk(m_mutex);

//            sql += "('" + it->first+ "','" + it->second.getText() + "','" + it->second.videoId() + "'," + std::to_string(it->second.user_id()) + "),";

//            //从对应缓存中删除相关数据
//            //erase的返回值是一个迭代器，指向删除元素下一个元素。
//            _newDirty.erase(it++);
//        }

        if (!sql.empty()) sql.pop_back();
        std::cout << sql << std::endl;
        insert(sql);   //执行批量插入，插入新的净缓存和新的脏缓存中的数据
    }
}

void CommentBroker::cacheDel()
{
    for(auto iter = _newDelete.begin(); iter != _newDelete.end();){

        //应该保证当进行插入时，数据是不可以被其他线程所更改的
        std::lock_guard<std::mutex> lk(m_mutex);

        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _newDelete.erase(iter++);
    }

    for(auto it = _oldDelete.begin(); it != _oldDelete.end();){

        //应该保证当进行插入时，数据是不可以被其他线程所更改的
        std::lock_guard<std::mutex> lk(m_mutex);

        std::string sql = "delete from comment where id='" + it->first + "'";
        del(sql);
        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _oldDelete.erase(it++);
    }


}

//void CommentBroker::cacheUpdate()
//{

//}


CommentBroker::CommentBroker()
{

}

std::shared_ptr<Comment> CommentBroker::inCache(std::string id)
{
    //判断是否在缓存中

    if (_newClean.count(id)) {
        return std::make_shared<Comment>(_newClean.at(id));
    }

//    if (_newDirty.count(id)) {
//        return std::make_shared<Comment>(_newDirty.at(id));
//    }

//    if (_newDelete.count(id)) {
//        return std::make_shared<Comment>(_newDelete.at(id));
//    }

    if (_oldClean.count(id)) {
        return std::make_shared<Comment>(_oldClean.at(id));
    }

//    if (_oldDirty.count(id)) {
//        return std::make_shared<Comment>(_oldDirty.at(id));
//    }

//    if (_oldDelete.count(id)) {
//        return std::make_shared<Comment>(_oldDelete.at(id));
//    }

    return nullptr;
}

int CommentBroker::judgeFromForDel(const std::string &id)
{
    if (_newClean.count(id)) return 0;
//    if (_newDirty.count(id)) return 1;
    if (_oldClean.count(id)) return 2;
//    if (_oldDirty.count(id)) return 3;

    //此时要删除的数据在数据库中，则从数据库读取数据，并将其放到旧的净缓存中
    return 2;
}
