// Copyright (C) Microsoft. All rights reserved. License (BSD/MIT/GPL)
// Project: kankan-Demo
//
// Author: Wenwen Cheng WennCheng@163.com)
// Date: 2022-07-25
// Version: 0.1.0
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Project description: kankan is a multimedia social platform based on video, and it is mainly for those who want to create and share, or spend their free time. It mainly provides people with the opportunity to disseminate videos and watch videos.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This file is part of kankan-Demo.
// History:
// 1.Modified by Wenwen Cheng (WennCheng@163.com) 2022-07-25
//   Description: 自定义定时器，与控制器对象生命周期相同。当构造控制器对象时，开启两个定时器，一个用来定时刷新每个代管者中的6个缓存，写入数据库，以此来减少数据库的读写次数。另一个用来定时刷新消息队列，查看消息队列中每个通知中的那些粉丝是否在线。当对象销毁时，才停止定时器。

#ifndef MYTIMER_H
#define MYTIMER_H


#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>

#include <iostream>
#include <thread>
#include <chrono>

class MyTimer
{
public:
    MyTimer(): _expired(true), _try_to_expire(false) {}

    MyTimer(const MyTimer& timer);

    ~MyTimer()
    {
        stop();
    }

    void start(int interval, std::function<void()> task);
    void stop();

private:
    std::atomic<bool> _expired; // timer stopped status
    std::atomic<bool> _try_to_expire; // timer is in stop process
    std::mutex _mutex;
    std::condition_variable _expired_cond;
};



#endif // MYTIMER_H
