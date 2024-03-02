#include <iostream>
#include <mutex>

// Lazy Initialization
class Singleton{
    
public:
    // 
    static Singleton& getInstance(){
        static Singleton instance;
        return instance;
    }

private:

    Singleton(){};

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