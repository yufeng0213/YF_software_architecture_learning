#include <iostream>
#include <memory>

int main() {
    // 通过new动态创建对象
    std::shared_ptr<int> ptr(new int(10));

    //使用make_shared创建对象(推荐) 内部优化了内存分配和引用计数管理
    std::shared_ptr<int> ptr2 = std::make_shared<int>(42);

    //
    //(*ptr).someMethod();// 访问和调用对象的方法
    *ptr2 = 50;//修改智能指针指向的对象

    // 复制构造，增加引用计数
    std::shared_ptr<int> ptr3(ptr2);

    //移动构造，减少引用计数 ptr2失去所有权，ptr2指向的资源被释放
    std::shared_ptr<int> ptr4 = std::move(ptr2);

    // 赋值，增加ptr4指向对象的引用计数
    ptr3 = ptr4;

    // 获取智能指针所管理的原始指针，但不改变引用计数
    int* rawPtr = ptr2.get();

    // 判断智能指针是否是唯一拥有该对象的指针
    if(ptr2.use_count() > 1){
        std::cout<<"ptr2 is not unique" << std::endl;
    }

    // 释放智能指针
    ptr2.reset();

    // 自定义删除器
    struct CustomerDeleter {
        void operator()(int* p) const {
            std::cout << "CustomerDeleter called" << std::endl;
            delete p;
        }
    };

    std::shared_ptr<int> ptr5(new int(),CustomerDeleter());

    // 弱引用指针，不增加引用计数
    std::weak_ptr<int> weakPtr(ptr2);
}