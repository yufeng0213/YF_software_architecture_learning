#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int callCount = 0;
    auto count{
        std::count_if(values.begin(), values.end(), [&callCount](int value) {
            ++callCount;
            return value % 2 == 0;
        })
    };

    std::cout << "Count: " << count << std::endl;
    std::cout << "Call count: " << callCount << std::endl;

    return 0;
}