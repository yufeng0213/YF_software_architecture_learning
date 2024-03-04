#include <iostream>
#include <memory>


struct CustomDeleter{
    void operator()(int* p){
        std::cout << "Custom Deleter called" << std::endl;
        delete p;
    }
};

int main(){

    //
    std::unique_ptr<int> uptr;

    //
    std::unique_ptr<int> ptr1(new int(10));

    //
    std::unique_ptr<int> ptr2 = std::make_unique<int>(20);

    //
    std::unique_ptr<int,CustomDeleter> ptr3(new int(30),CustomDeleter());

    //
    std::unique_ptr<int> ptr_source(new int(40));
    std::unique_ptr<int> ptr_target = std::move(ptr_source);

    //
    ptr_target = std::make_unique<int>(50);

    
    return 0;
}