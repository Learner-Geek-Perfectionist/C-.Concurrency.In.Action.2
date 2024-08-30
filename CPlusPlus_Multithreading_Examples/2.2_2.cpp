//
// Created by xin on 24-8-31.
// 在线程上启动类中的成员函数，并且传递参数
// 通过类对象调用成员函数，编译器会隐式添加 this 参数，即 &obj
// 比如，有一个 Example 类，有一个成员函数 func(int x), obj 是该类的对象，调用 obj.func(2);
// 相当于 Example::func(&obj,2);  在 obj.func(2); 形式中， this 指针被隐藏了。

#include <memory>
#include <iostream>
#include <thread>
using namespace std;


class X
{
public:
    void do_lengthy_work()
    {
        cout << "do some work\n";
    }
};

X my_x;

int main()
{
    std::thread t(&X::do_lengthy_work, &my_x);
    t.join();
}
