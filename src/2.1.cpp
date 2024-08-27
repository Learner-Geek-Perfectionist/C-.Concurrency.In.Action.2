#include <iostream>
#include <thread>
using namespace std;

struct fun {
    int i;
    fun(int &x):i(x){}
    void f(int x) {
        if(x==100) cout<<"success"<<endl;
        else cout<<"false"<<endl;
    }
    void operator()() {
        for(int j=0;j<10000;j++) {
        } // 先让 main 线程结束，再执行 t 线程。
        f(100);
    }
};
int main() {
    int i=100;
    fun my_fun(i);
    thread t(my_fun);
    t.detach();  // 分离进程
    // t.join()(); // 若等待进程，输出 success
}