//
// Created by xin on 24-8-30.
// const & 引用可以绑定 右值和左值，但是 & 普通引用只能绑定左值
// 因此，如果子线程上的函数的参数列表是 & 普通引用，而线程 thread 构造函数又以右值的形式拷贝到子线程的内存空间中，然后再传递给函数，
// 但是函数的参数列表是左值引用，只能接受左值，无法接受右值参数。


#include <iostream>
#include <memory>
#include <thread>
using namespace std;

class widget_id
{
};

class widget_data
{
};

void display_status()
{
    cout << "display status\n";
}

void process_widget_data(widget_data)
{
    cout << "process_data\n";
}


void update_data_for_widget(widget_id w, widget_data& data) // 修改为 const widget_data& data 能正确输出，
{
};

void oops_again(widget_id w)
{
    widget_data data;
    std::thread t(update_data_for_widget, w, data);
    display_status();
    t.join();
    process_widget_data(data);
}

int main()
{
    widget_id id;
    oops_again(id); // 报错
}
