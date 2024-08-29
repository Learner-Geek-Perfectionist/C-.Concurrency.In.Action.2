//
// Created by xin on 24-8-28.
// 向线程函数传递参数

#include <iostream>
#include <thread>
#include <string>
using namespace std;

void f(int i, string const& s)
{
    std::this_thread::sleep_for(std::chrono::seconds(3)); // 模拟耗时操作
    cout << i << endl << s << endl;
}

void oops(int some_param)
{
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    thread t(f, 3, (buffer)); // 传递参数的时候使用了函数的局部变量。
    t.detach();
}

int main()
{
    oops(123);
    std::this_thread::sleep_for(std::chrono::seconds(5)); // 模拟耗时操作
}
