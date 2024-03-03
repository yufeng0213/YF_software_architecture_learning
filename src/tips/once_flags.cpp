#include <mutex>
#include <iostream>
#include <thread>

/*std::once_flag 是 C++11 引入的标准库组件，位于 <mutex> 头文件中，
旨在提供一种线程安全的方式来确保某个操作在整个程序生命周期内只执行一次。
这个特性对于实现线程安全的单例模式以及其他需要进行一次性初始化的场景非常有用*/


// 假设这是需要进行一次性初始化的资源
void initResource(){
    std::cout<<"Resource initialized.\n";
    // 实际初始化资源的代码
}

// 全局once_flag 对象
std::once_flag resourceInitFlag;

void useResource(){

    // 使用std::call_once 来确保initResource 函数仅被执行一次0
    std::call_once(resourceInitFlag,initResource);

    // 此处假设已经安全地使用了已初始化的资源
    std::cout<<"Using the initialized resource...\n";
}

int main(){
    std::thread t1(useResource);
    std::thread t1(useResource);
    t1.join();
    t2.join();

    return 0;
}
