//
// Created by xin on 24-8-28.
// 利用 RAII 过程等待线程完结

#include <iostream>
#include <thread>
using namespace std;


struct func
{
    int& i;

    func(int& i_): i(i_)
    {
    }

    void operator()()
    {
        for (unsigned j = 0; j < 5; ++j)
            do_something(i);
    }
};

void do_something(int i)
{
    if (i == 0) cout << "success\n";
    else cout << "failure\n";
}

class thread_guard
{
    std::thread& t;

public:
    explicit thread_guard(std::thread& t_): t(t_)
    {
    }

    ~thread_guard()
    {
        if (t.joinable()) t.join();
    }

    // 线程不能被拷贝，因此拷贝构造函数和拷贝赋值运算符被删除。
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    do_something_in_current_thread();
}

int main()
{
}
