//
// Created by xin on 24-8-27.
// 前线程的函数已返回，新线程却仍能访问其局部变量
// 以下做法极不可取：意图在函数中创建线程(比如，在oops()函数中创建线程，my_thread)，
// 并让线程访问(oops)函数的局部变量(比如，my_thread线程访问局部变量some_local_state)

#include <iostream>
#include <thread>
using namespace std;

void do_something(int i)
{
    if (i == 0) cout << "success\n";
    else cout << "failure\n";
}

struct func
{
    int& i;

    func(int& i_): i(i_)
    {
    }

    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
        {
            do_something(i);
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
    // my_thread.join();
}


int main()
{
    oops();
}
