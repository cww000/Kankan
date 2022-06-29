#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H

#include <unordered_map>
#include <mariadb/conncpp.hpp>
#include "cache.h"

class RelationalBroker
{
public:
    RelationalBroker();
    virtual ~RelationalBroker();

    //执行数据库查询操作，返回数据集
    //sql:SQL语句
    sql::ResultSet* query(std::string sql);

    //执行数据库插入操作
    //sql:SQL语句
    void insert(std::string sql);
private:
    std::unordered_map<std::string, Cache> _caches;
    std::unique_ptr<sql::Connection> conn;
};

#endif // RELATIONALBROKER_H
