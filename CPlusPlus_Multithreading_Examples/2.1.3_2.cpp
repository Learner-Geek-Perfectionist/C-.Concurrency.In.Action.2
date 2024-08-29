//
// Created by xin on 24-8-29.
//
// Case 3，try-catch处理

#include <iostream>
#include <thread>
#include <stdexcept>

void threadFunction()
{
    std::cout << "Thread is running...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟工作
    std::cout << "Thread finished its work.\n";
}

int main()
{
    std::thread t(threadFunction);
    std::cout << "Main thread is performing an operation...\n";
    try
    {
        // 模拟一个可能抛出异常的操作
        throw std::runtime_error("An error occurred!");
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
        t.join();  // 正确处理线程，确保线程完成
        return 1;  // 由于异常，提前退出

        // 因为异常，这里没有调用 join()
    }
    if (t.joinable()) t.join();
    std::cout << "Main thread ended without waiting for the thread.\n";
    return 0;
}
