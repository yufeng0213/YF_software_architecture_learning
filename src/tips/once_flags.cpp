#include <mutex>
#include <iostream>
#include <thread>
void initResource(){
    std::cout<<"Resource initialized.\n";
    //
}

std::once_flag resourceInitFlag;

void useResource(){

    std::call_once(resourceInitFlag,initResource);

    //
    std::cout<<"Using the initialized resource...\n";
}

int main(){
    std::thread t1(useResource);
    std::thread t1(useResource);

    return 0;
}