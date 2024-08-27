//
// Created by xin on 24-8-27.
//

#include <iostream>
#include <thread>
using namespace std;

void f()
{
    cout << "Hello Concurrent World";
}

int main()
{
    thread t(f);
    for (int i = 0; i < 1000000; i++)
    {
    }
    t.join();
}
