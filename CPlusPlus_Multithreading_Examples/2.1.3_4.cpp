//
// Created by xin on 24-8-29.
// 使用智能指针实现伪闭包（pseudo-closure）
// 用 std::shared_ptr 来安全地在 lambda 表达式中捕获这些资源，确保在使用这些资源的过程中它们不会被意外释放。

#include <iostream>
#include <memory>
#include <thread>

void startBackgroundTask(std::shared_ptr<int> data)
{
    // 创建一个线程，捕获data
    std::thread t([data]()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Data: " << *data << std::endl;
    });
    t.detach(); // 分离线程，让它在后台运行
}

int main()
{
    std::shared_ptr<int> data = std::make_shared<int>(42);

    startBackgroundTask(data);

    std::this_thread::sleep_for(std::chrono::seconds(2)); // 等待足够长的时间以确保线程执行完成
    return 0;
}
