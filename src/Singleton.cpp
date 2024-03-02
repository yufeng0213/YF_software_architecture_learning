#include <iostream>
#include <mutex>

// 饿汉式
class Singleton{
    
public:
    // 提供全局访问接口
    static Singleton& getInstance(){
        // 由于静态局部变量只在第一次调用时初始化
        // 因此可以保证线程安全性和单例性
        static Singleton instance;
        return instance;
    }

private:
    // 构造函数私有化
    Singleton(){};
    // 禁止拷贝构造和赋值操作
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

};

class Singleton2{
private:
    static Singleton2* instance;

    static std::mutex m;

    Singleton2(){};

    Singleton2(const Singleton2&) = delete;
    Singleton2& operator=(const Singleton2&) = delete;

public:

    static Singleton2& getInstance(){
        std::lock_guard<std::mutex> lock(m);
        if(instance == nullptr){
            instance = new Singleton2();
        }

        return *instance;
    }

    ~Singleton2(){
        if(instance != nullptr){

            delete instance;
            instance = nullptr;
        }
    }
};


int main(){

    // 
    Singleton& s = Singleton::getInstance();

    Singleton2& s = Singleton2::getInstance();

    return 0;
}
