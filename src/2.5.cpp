//
// Created by xin on 24-8-31.
// 从函数内部返回 std::thread 对象

#include <memory>
#include <iostream>
#include <thread>
using namespace std;

void some_function()
{
    cout << "some_function\n";
}

void some_other_function(int x)
{
    cout << "some_other_function: " << x << endl;
}

thread f()
{
    return thread(some_function);
}

thread g()
{
    thread t(some_other_function, 42);
    return t; //返回亡值(属于右值的一种)
}

int main()
{
    thread t1 = f();
    thread t2 = g();
    t1.join(), t2.join();
}
