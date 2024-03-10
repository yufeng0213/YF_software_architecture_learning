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

    return 0;
}