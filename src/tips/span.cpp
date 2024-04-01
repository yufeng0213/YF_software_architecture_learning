#include <iostream>
#include <span>
#include <vector>
#include <algorithm>

/**
 * 获取一个向量的子向量，并以span的形式返回。
 *
 * @param vec 引用类型的向量，函数将从中获取子向量。
 * @param start 子向量的起始索引。
 * @param count 子向量包含的元素数量。
 * @return 如果成功，返回一个span，它引用向量vec中从start开始的count个元素；如果失败，返回一个空的span。
 */
std::span<int> getSubvector(std::vector<int>& vec, size_t start, size_t count) {
    if (start + count <= vec.size()) {
        return std::span<int>(vec.data() + start, count);
    }

    // 根据错误处理策略，这里可以返回空span或抛出异常
    return std::span<int>();
}

int main() {
    // 使用span处理连续内存范围，提高代码的安全性和简洁性

    // 1. 传递子范围
    std::vector<int> v{1, 2, 3, 4, 5};
    std::span<int> s1{v.begin(), v.end()};
    // 传递索引1到2（不包括2）的子范围
    std::span<int> s2{v.begin() + 1, v.begin() + 3};
    // 2. 返回子范围
    // 函数可以返回一个基于std::vector内存的std::span，以便调用者能读但不修改
    // （或根据需要修改）vector的部分内容，而不暴露vector本身。
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::span<int> sub_span = getSubvector(numbers, 1, 3);
    for (int& num : sub_span) { // 用& 引用才能修改
        std::cout << num << " ";
        num = 0; // 修改span中的元素也会修改原向量中的对应元素
    }

    std::cout << "\n";

    std::for_each(numbers.begin(), numbers.end(), [](int i) {
        std::cout << i << " ";
    });

    return 0;
}
