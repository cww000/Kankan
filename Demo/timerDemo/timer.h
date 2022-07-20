#ifndef TIMER_H
#define TIMER_H

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

class Timer
{
public:
    Timer(): _expired(true), _try_to_expire(false) {}

    Timer(const Timer& timer);

    ~Timer()
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


#endif // TIMER_H
