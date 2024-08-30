//
// Created by xin on 24-8-31.
// 线程权转移
// 正在关联的线程对象不能临时去关联另一个线程，防止任务执行一半导致发生错误❌！

#include <memory>
#include <iostream>
#include <thread>
using namespace std;


void some_function()
{
    cout << "some_function\n";
}

void some_other_function()
{
    cout << "some_other_function\n";
}

int main()
{
    thread t1(some_function); // t1 关联 some_function
    thread t2 = std::move(t1); // t2 关联 some_function，t1 为空
    t1 = thread(some_other_function); // t1 关联 some_other_function，t2 关联 some_function
    thread t3;
    t3 = move(t2); // t3 关联 some_function,t2 为空,t1 关联 some_other_function
    t1 = move(t3); //报错， t1 正在运行 some_other_function 函数，无法关联去运行 some_function 任务。
    t3.join(), t1.join();
}
