#include <iostream>
#include <memory>


struct CustomDeleter{
    void operator()(int* p){
        std::cout << "Custom Deleter called" << std::endl;
        delete p;
    }
};

int main(){

    // 初始化为空
    std::unique_ptr<int> uptr;

    // 直接初始化指向动态分配的对象
    std::unique_ptr<int> ptr1(new int(10));// 创建一个存储10的int型智能指针

    // 使用std::make_unique 创建（推荐，避免直接new）
    // 1. 可以强制初始化，避免忘记
    // 2. 类型安全，可以自动推导
    // 3. new需要手动管理异常抛出
    std::unique_ptr<int> ptr2 = std::make_unique<int>(20);

    // 自定义删除器
    std::unique_ptr<int,CustomDeleter> ptr3(new int(30),CustomDeleter());

    // 移动构造函数，转移所有权
    std::unique_ptr<int> ptr_source(new int(40));
    // 移动后，ptr_source 不再拥有任何资源
    std::unique_ptr<int> ptr_target = std::move(ptr_source);

    // 移动赋值，旧资源被释放
    ptr_target = std::make_unique<int>(50);

     
    return 0;
}
