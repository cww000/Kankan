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
