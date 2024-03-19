#include <iostream>
#include <numeric>
#include <vector>
#include <execution>

/*
 * std::transform_reduce 是C++17 引入的标准库算法，它结合了std::transform 和 std::accumulate的功能，可以先对指定范围内的元素应用一个单目操作，
 * 然后再将结果累加起来。这个算法特别适用于需要先转换数据然后进行某种形式的聚合操作的情况。并且它可以利用执行策略来进行并行计算以提高性能。
 *
 */
// 转换操作
auto square = [](int x) { return x * x; };

// 累加操作
auto add = [](int x, int y) { return x + y; };

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    // 初始化累加器
    int initial_value = 0;

    // 使用默认的顺序执行策略
    auto result = std::transform_reduce(v.begin(), v.end(), initial_value, add, square);
    std::cout<<"result: "<<result<<std::endl;

    auto result2 = std::transform_reduce(std::execution::seq, v.begin(), v.end(), initial_value, add, square);
    std::cout<<"result2: "<<result2<<std::endl;

    auto result3 = std::transform_reduce(std::execution::par, v.begin(), v.end(), initial_value, add, square);
    std::cout<<"result3: "<<result3<<std::endl;

    return 0;
}