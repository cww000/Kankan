#include "mytimer.h"



MyTimer::MyTimer(const MyTimer &timer)
{
    _expired = timer._expired.load();
    _try_to_expire = timer._try_to_expire.load();
}

void MyTimer::start(int interval, std::function<void ()> task)
{
    if (_expired == false)
        return;

   //开启一个异步的定时器
    _expired = false;
    std::thread([this, interval, task]() {
        while (!_try_to_expire)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            task();
        }

        {
           //停止定时器，唤醒主线程
            std::lock_guard<std::mutex> locker(_mutex);
            _expired = true;
            _expired_cond.notify_one();
        }
    }).detach();  //主调线程继续运行，被调线程驻留后台运行，主调线程无法再取得该被调线程的控制权
}

void MyTimer::stop()
{
    if (_expired)
        return;

    if (_try_to_expire)
        return;

    _try_to_expire = true;
    {
        std::unique_lock<std::mutex> locker(_mutex);
        _expired_cond.wait(locker, [this] {return _expired == true; });

        // reset the timer
        if (_expired == true)
            _try_to_expire = false;
    }
}
