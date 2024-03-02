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

// 懒汉式
class Singleton2{
private:
    // 静态单例实例
    static Singleton2* instance;
    // 确保线程安全的互斥锁
    static std::mutex m;

    // 构造函数私有化
    Singleton2(){};
    // 禁止拷贝构造和赋值操作
    Singleton2(const Singleton2&) = delete;
    Singleton2& operator=(const Singleton2&) = delete;

public:

    // 提供全局访问接口
    static Singleton2& getInstance(){
        std::lock_guard<std::mutex> lock(m); // 保证线程安全
        if(instance == nullptr){
            instance = new Singleton2();
        }
        return *instance;
    }

    // 可选的析构函数，如果需要删除单例应在程序退出时手动调用
    // 注意： 在C++11之后，智能指针可以更好的管理单例资源
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
