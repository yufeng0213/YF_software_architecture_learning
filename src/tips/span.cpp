#include <iostream>
#include <span>
#include <vector>

// span 主要是在C++20中加入的，是一段连续内存的指针，可以避免在使用过程中越界的问题。
int main() {

    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> v2;

    std::span<int> s1{v};


    return 0;
}