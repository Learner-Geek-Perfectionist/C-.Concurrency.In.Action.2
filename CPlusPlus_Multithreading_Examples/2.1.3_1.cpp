//
// Created by xin on 24-8-28.
// 如果在启动线程之后、调用 join() 之前发生了异常，那么 join() 的调用可能会被跳过。
// 在这个例子中，线程对象 t 被创建之后，子线程立马启动，同时主线程也在执行，当主线程执行到 throw 抛出异常时，子线程还在 sleep，
// 此时子线程终止，转向 catch 块
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
    try
    {
        std::thread t(threadFunction);

        // 模拟一个可能抛出异常的操作
        std::cout << "Main thread is performing an operation...\n";
        throw std::runtime_error("An error occurred!");

        // 如果没有异常，这里会调用 join()
        t.join();
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
        // 因为异常，这里没有调用 join()
    }

    std::cout << "Main thread ended without waiting for the thread.\n";
    return 0; // 程序可能在子线程完成前就退出了
}
