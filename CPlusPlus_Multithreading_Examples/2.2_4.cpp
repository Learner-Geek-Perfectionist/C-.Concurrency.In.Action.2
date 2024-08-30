//
// Created by xin on 24-8-31.
// 使用 move 对 unique_ptr 进行移动


#include <memory>
#include <iostream>
#include <thread>
using namespace std;

class big_object
{
public:
    void prepare(int x) { cout << "preparing data：" << x << endl; }
};

void process_big_object(unique_ptr<big_object>)
{
    cout << "processing data\n";
}


int main()
{
    unique_ptr<big_object> p(new big_object); // 创建独占指针，管理 big_object 类资源
    p->prepare(42); // big_object 对象准备数据
    thread t(process_big_object, std::move(p)); // 将 big_object 对象的管理权转移到子线程中。
    // 1.thread 的构造函数将 std::move(p) 右值拷贝到子线程内部
    // 2.然后 process_big_object 函数再调用参数。
    t.join();
}
