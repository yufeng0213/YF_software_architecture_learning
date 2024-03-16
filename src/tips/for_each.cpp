#include <iostream>
#include <array>
#include <Algorithm>
#include <vector>

struct MyClass{
    void print(){
        srand(1);
        i = rand();
        std::cout<<this->i<<" ";
    }

    int i;
};

int main() {

    // for_each 的遍历举例
    std::array<int,10> arr = {1,2,3,4,5,6,7,8,9,10};

    std::for_each(arr.begin(),arr.end(),[](int& i){
        std::cout<<i<<" ";
    });

    std::cout<<std::endl;

    std::vector<int> vec;
    vec.resize(10);
    std::for_each(vec.begin(),vec.end(),[](int& i){
        std::cout<<i<<" ";
    });

    std::cout<<std::endl;

    std::vector<MyClass> vec2;
    vec2.resize(10);
    std::for_each(vec2.begin(),vec2.end(),[](MyClass& i){
        i.print();
    });

    std::cout<<std::endl;

    // for_each 修改值
    std::vector<int> vec3;
    vec3.resize(10);
    std::for_each(vec3.begin(),vec3.end(),[](int& i){
        i = rand();
    });

    std::for_each(vec3.begin(),vec3.end(),[](int& i){
        std::cout<<i<<" ";
    });


    // 自定义函数，使用操作符
    struct printer{
        void operator()(int& i){
            std::cout<<"Num: "<<i<<std::endl;
        }
    };

    std::vector<int> vec4;
    vec4.resize(10);
    std::for_each(vec4.begin(),vec4.end(),printer());

    return 0;
}