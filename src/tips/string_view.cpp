// string_view.cpp

#include <iostream>
#include <string_view>

int main(){

    // 从std::string 创建string_view
    std::string str1 = "Hello, world!";
    std::string_view sv2 = str1;// 直接转换
    std::string_view sv3 = str1.substr(0,5);// 从子串创建

    // 从C风格字符串创建
    char cstr[] = "C-style string";
    std::string_view sv4(cstr);

    // 从字符数组和长度创建
    char array[] = {'H', 'e', 'l', 'l', 'o'};
    // 减去1，因为末尾有'\0'
    std::string_view sv5(array, sizeof(array) - 1);

    // 空string_view
    std::string_view empty_sv;

    return 0;
}