//
// Created by xin on 24-8-29.
//
// Case 4，RAII手法

#include <iostream>
#include <thread>
#include <stdexcept>

void threadFunction()
{
    std::cout << "Thread is running...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟工作
    std::cout << "Thread finished its work.\n";
}

class thread_guard
{
    std::thread& t;

public:
    explicit thread_guard(std::thread& t_) : t(t_)
    {
    }

    ~thread_guard()
    {
        if (t.joinable()) t.join();
    }

    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

int main()
{
    std::thread t(threadFunction);
    std::cout << "Main thread is performing an operation...\n";
    thread_guard g(t);
    std::cout << "Main thread ended without waiting for the thread.\n";
    return 0; // 程序可能在子线程完成前就退出了
}
