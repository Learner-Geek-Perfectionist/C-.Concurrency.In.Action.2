//
// Created by xin on 24-8-31.
// 生成多个线程，并等待它们完成运行

// cout 的非原子性：这导致输出结果是混乱的。

// 在cout 中，每次输出到控制台的操作实际上涉及多个步骤，比如：
//
//     1.	将数据从内存中读取出来。
//     2.	格式化数据（如将整数转换为字符串）。
//     3.	将数据写入缓冲区。
//     4.	将缓冲区的内容刷到输出设备（如屏幕）。
//
// 这些步骤每一个都可能在执行过程中被打断，导致多个线程的操作交织在一起。


// 假设有两个线程 A 和 B，它们分别要输出 1 do_work 和 2 do_work。

// 但由于 cout 不是原子操作，这个过程可能会被打断，导致输出结果混合在一起。例如，可能会发生如下情况：
//
//     1.	线程 A 开始执行 cout，输出 “1”。
//     2.	在线程 A 尚未完成输出 “ do_work” 之前，线程 B 被操作系统调度器分配到 CPU 执行，开始输出 “2”。
//     3.	线程 B 可能先输出 “2”，然后再输出 “ do_work”。
//     4.	最后线程 A 继续输出 “ do_work”。

#include <memory>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void do_work(unsigned id)
{
    cout << id << " do_work\n";
}

void f()
{
    vector<thread> threads;
    for (unsigned i = 0; i < 20; i++)
    {
        threads.emplace_back(do_work, i + 1); // 生成线程
    }
    for (auto& entry : threads) entry.join(); // 对各个线程调用 join()
}

int main()
{
    f();
}
