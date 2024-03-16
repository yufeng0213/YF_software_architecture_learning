#include <iostream>

union MyUnion {

    int intVal; // 整数值
    double doubleVal;
    float floatVal;
    char charVal;
    char charArr[17]; // 字符数组
};


int main() {

    MyUnion myUnion;
    std::cout<<"my union size : "<<sizeof(myUnion)<<std::endl;

    MyUnion myUnion2;
    myUnion2.intVal = 100;
    std::cout<<"my union2 intVal : "<<myUnion2.intVal<<std::endl;
    //
    std::cout<<"my union2 doubleVal : "<<myUnion2.doubleVal<<std::endl;

    return 0;
}