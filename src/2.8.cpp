//
// Created by xin on 24-8-31.
// 生成多个线程，并等待它们完成运行


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
