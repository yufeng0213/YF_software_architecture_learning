#include <iostream>
#include <memory>

int main() {
    //
    std::shared_ptr<int> ptr(new int(10));

    //
    std::shared_ptr<int> ptr2 = std::make_shared<int>(42);

    //
    //(*ptr).someMethod();
    *ptr2 = 50;

    //
    std::shared_ptr<int> ptr3(ptr2);

    //
    std::shared_ptr<int> ptr4 = std::move(ptr2);

    ptr3 = ptr4;

    //
    int* rawPtr = ptr2.get();

    //
    if(ptr2.use_count() > 1){
        std::cout<<"ptr2 is not unique" << std::endl;
    }

    //
    ptr2.reset();

    //
    struct CustomerDeleter {
        void operator()(int* p) const {
            std::cout << "CustomerDeleter called" << std::endl;
            delete p;
        }
    };

    std::shared_ptr<int> ptr5(new int(),CustomerDeleter());

    //
    std::weak_ptr<int> weakPtr(ptr2);
}