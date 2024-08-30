//
// Created by xin on 24-8-31.
// coped_thread 类及其用例

#include <memory>
#include <iostream>
#include <thread>
using namespace std;

void do_something(int i)
{
    if (i == 0) cout << "success\n";
    else cout << i << ": failure\n";
}

void do_something_in_current_thread()
{
    for (int i = 0; i < 5; i++)
        cout << "Main thread is running...... \n";
}

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


class thread_guard
{
    std::thread& t;

public:
    explicit thread_guard(std::thread& t_) : t(t_)
    {
    }

    ~thread_guard()
    {
        if (t.joinable()) t.join();
    }

    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};


class scoped_thread
{
    thread t;

public:
    explicit scoped_thread(thread _t): t(move(_t))
    {
        if (!t.joinable()) throw logic_error("No thread"); // 若无线程，则抛出异常。
    }

    ~scoped_thread() { t.join(); } // 无需再判断线程是否可汇合。
    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
};

void f()
{
    int some_local_state; // 未定义的值......
    scoped_thread t{std::thread(func(some_local_state))}; // 先构造临时的函数对象，再构造临时的线程对象
    do_something_in_current_thread();
}

int main()
{
    f();
}
