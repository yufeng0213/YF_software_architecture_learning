#include <iostream>
#include <string>
using namespace std;

struct A {
    std::string str;
};

class B {
public:
    B() = default;
    ~B() = default;

    size_t a[10];
    static size_t b;
};

/*
 * Debug 和 release 模式下 sizeof 的结果不同
 *  static 的成员变量不会参与 sizeof 的计算
 *  class 的 function 不占用内存，只有成员变量占用内存
 */
int main()
{
    std::string str;
    std::cout << "sizeof: " << sizeof(str) << "\n";
    std::string str2 = "";
    std::cout << "sizeof2:" << sizeof(str2) << "\n";
    std::string str3 = "helloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworldhelloworld";
    std::cout << "sizeof3:" << sizeof(str3) << "\n";
    char* pch;
    std::cout << "sizeof pch: " << sizeof(pch) << "\n";
    double* pdb;
    std::cout << "sizeof pdb: " << sizeof(pdb) << "\n";
    int* pint;
    std::cout << "sizeof pint: " << sizeof(pint) << "\n";
    std::cout << "sizeof struct:" << sizeof(A) << "\n";
    B b;
    std::cout << "sizeof B: " << sizeof(b) << "\n";
    std::cout << "sizeof long long " << sizeof(long long) << "\n";
    std::cout << "sizeof long " << sizeof(long) << "\n";
    return 0;
}