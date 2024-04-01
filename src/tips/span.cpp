#include <iostream>
#include <span>
#include <vector>
#include <Algorithm>

// 是不是相当于有人在用array，有人用vector时，使用span能更好的传递数据？

std::span<int> getSubvector(std::vector<int>& vec,size_t start,size_t count){
    if(start+count <= vec.size()){
       return std::span<int>(vec.data()+start,count);
        //std::span<int> s(vec.data()+start,count);
    }

    // 返回空span或抛出异常，取决于错误处理策略
    return std::span<int>();
}

// span 主要是在C++20中加入的，是一段连续内存的指针，可以避免在使用过程中越界的问题。
int main() {

    // 1. 传递子范围
    std::vector<int> v{1, 2, 3, 4, 5};
    std::span<int> s1{v.begin(), v.end()};
    // 传递索引1到2（不包括2）的子范围
    std::span<int> s2{v.begin()+1,v.begin()+3};
    //2. 返回子范围
    // 函数可以返回一个基于std::vector内存的std::span，以便调用者能读但不修改
    // （或根据需要修改）vector的部分内容，而不暴露vector本身。
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::span<int> sub_span = getSubvector(numbers, 1, 3);
    for (int& num : sub_span) {// 用& 引用才能修改
        std::cout << num << " ";
        num = 0;
    }

    std::cout<<"\n";

    std::for_each(numbers.begin(),numbers.end(),[](int i){
        std::cout<<i<<" ";
    });




    return 0;
}