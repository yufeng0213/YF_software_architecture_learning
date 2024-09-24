#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

int main() {

    WSADATA wsaData;

    int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        std::cerr << "Failed to initialize Winsock: " << wsResult << std::endl;
        return 1;
    }

    const char* server = "www.example.com";
    const char* path = "/get";

    SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket() : " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80);
    serverAddress.sin_addr.s_addr = inet_addr("93.184.215.14");//inet_addr(server);

    int connectResult = connect(connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
    if (connectResult == SOCKET_ERROR) {
        std::cerr << "Could not connect to the server: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    const char* request = std::string("GET " + std::string(path) + " HTTP/1.1\r\n" + "HOST: "+std::string(server) + "\r\n" + "Connection: close\r\n" + "\r\n").c_str();
    int bytesSent = ::send(connectSocket, request, (int)strlen(request), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    char responseBuffer[4096];
    int bytesReceived = 0;
    std::string responseData;

    do {
        bytesReceived = ::recv(connectSocket, responseBuffer, 4096, 0);
        if (bytesReceived > 0) {
            responseData.append(responseBuffer, bytesReceived);
        }
    } while (bytesReceived > 0);

    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Error receiving data: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Response: \n" << responseData << std::endl;

    closesocket(connectSocket);

    WSACleanup();

    return 0;
}