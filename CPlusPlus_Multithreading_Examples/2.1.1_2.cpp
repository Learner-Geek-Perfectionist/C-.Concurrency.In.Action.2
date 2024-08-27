//
// Created by xin on 24-8-27.
// 如果选择了分离，且分离时「子线程」还未结束运行，那它将继续运行，甚至在 std::thread 对象销毁很久之后依然运行，
// 它只有最终从线程函数返回时才会结束运行。
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> isRunning{false};

void my_fun()
{
    int cnt = 0;
    isRunning = true;
    while (1)
    {
        cnt++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "running\n";
        if (cnt == 5)break;
    }
    isRunning = false;
}

void f()
{
    std::thread t(my_fun);
    t.detach(); // 分离线程
    std::cout << "Thread object in f() is about to be destroyed.\n";
}

int main()
{
    f();
    if (isRunning)
    {
        std::cout << "Detached thread is still running.\n";
    }
    else
    {
        std::cout << "Detached thread has completed.\n";
    }

    // 继续等待确保子线程完成
    std::this_thread::sleep_for(std::chrono::seconds(6));
    if (!isRunning)
    {
        std::cout << "Main thread: Detached thread has definitely stopped.\n";
    }

    return 0;
}
