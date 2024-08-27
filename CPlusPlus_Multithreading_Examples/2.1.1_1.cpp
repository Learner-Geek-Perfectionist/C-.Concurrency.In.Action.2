//
// Created by xin on 24-8-27.
//
// 如果主线程结束，则操作系统回收进程的所有资源，因此，分离的子线程也被迫结束。
// 因此 main 线程等待的时间必须长于子线程。
#include <iostream>
#include <thread>
#include <chrono>

void run()
{
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟耗时操作
    std::cout << "Thread completed." << std::endl;
}

int main()
{
    std::thread t(run);
    t.detach(); // 分离线程

    std::cout << "Main thread is free to do other things." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 主线程等待 2 秒

    return 0;
}
