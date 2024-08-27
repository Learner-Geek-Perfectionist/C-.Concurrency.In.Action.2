//
// Created by xin on 24-8-28.
//
#include <iostream>
#include <thread>
using namespace std;

void do_something(int i)
{
    if (i == 0) cout << "success\n";
    else cout << "failure\n";
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


void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try
    {
        do_something_in_current_thread();
    }
    catch (...)
    {
        t.join();
        throw;
    }
    t.join();
}


int main()
{
    f();
}
