#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
//
void readFile() {
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, // 使用分页文件
                                        NULL,					// 默认安全属性
                                        PAGE_READWRITE,			// 独写权限
                                        0,						// 高32位文件大小
                                        4096,					// 低32位文件大小
                                        L".\MySharedMemory" // 对象名字
    );
    if (hMapFile == NULL) {
        std::cerr << "Could not create file mapping object(" << GetLastError() << ").\n";
        return;
    }

    void* pBuf = MapViewOfFile(hMapFile, // 映射对象的句柄
                               FILE_MAP_ALL_ACCESS, // 访问权限
                               0,					// 文件偏移量，高32位
                               0,					// 文件偏移量，低32位
                               0					// 映射的视图大小，0表示映射整个文件
    );
    if (pBuf == NULL) {
        std::cerr << "Could not map view of file (" << GetLastError() << ").\n";
        CloseHandle(hMapFile);
        return;
    }

    int count = 0;
    while (true) {
        //std::memcpy(pBuf, "Hello World.", 13);
        std::cout <<" recv data : [" << count++ << "]: " << std::string(static_cast<char*>(pBuf)) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (!UnmapViewOfFile(pBuf)) {
        std::cerr << "Could not unmap view of file (" << GetLastError() << ").\n";
    }

    if (!CloseHandle(hMapFile)) {
        std::cerr << "Could not close handle to file mapping object (" << GetLastError() << ").\n";
    }
}

void writeFile() {
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, // 使用分页文件
                                        NULL,					// 默认安全属性
                                        PAGE_READWRITE,			// 独写权限
                                        0,						// 高32位文件大小
                                        4096,					// 低32位文件大小
                                        L".\MySharedMemory" // 对象名字
    );
    if (hMapFile == NULL) {
        std::cerr << "Could not create file mapping object(" << GetLastError() << ").\n";
        return;
    }

    void* pBuf = MapViewOfFile(hMapFile, // 映射对象的句柄
                               FILE_MAP_ALL_ACCESS, // 访问权限
                               0,					// 文件偏移量，高32位
                               0,					// 文件偏移量，低32位
                               0					// 映射的视图大小，0表示映射整个文件
    );
    if (pBuf == NULL) {
        std::cerr << "Could not map view of file (" << GetLastError() << ").\n";
        CloseHandle(hMapFile);
        return;
    }

    int index = 0;
    while (true) {
        std::memcpy(pBuf, "Hello World.", 13);
        std::cout << "send data : [" << index++ << "]\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    if (!UnmapViewOfFile(pBuf)) {
        std::cerr << "Could not unmap view of file (" << GetLastError() << ").\n";
    }

    if (!CloseHandle(hMapFile)) {
        std::cerr << "Could not close handle to file mapping object (" << GetLastError() << ").\n";
    }

}
int main() {

    std::thread thSend(writeFile);
    std::thread thRecv(readFile);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
