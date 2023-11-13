#include <iostream>
#include <winsock2.h>
#include <vector>
#include "event.h"

#pragma comment(lib, "ws2_32.lib") // 链接到winsock库


void handle(char *data, size_t data_size) {
    if (data_size < sizeof(int)) {
        return;
    }
    int *count = reinterpret_cast<int *>(data);

    if (data_size < sizeof(int) + (*count) * sizeof(Event)) {
        return;
    }
    char *p = data + 4;
    for (int i = 0; i < (*count); i++) {
        Event *event = reinterpret_cast<Event *>(p);
        switch (event->type) {
            case MOUSE_MOVE:
                event->MouseMove();
                break;
        }
        p += sizeof(Event);
    }


}

int main() {
    // 初始化Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    // 创建一个UDP套接字
    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
        WSACleanup();
        return 1;
    }

    // 设置服务器地址信息
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // 使用端口12345，你可以根据需要更改
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定套接字
    if (bind(serverSocket, reinterpret_cast<SOCKADDR *>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error" << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "UDP server is listening on port 12345" << std::endl;

    // 接收数据
    char buffer[1024];
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    int recvResult;

    while (true) {
        recvResult = recvfrom(serverSocket, buffer, sizeof(buffer), 0, reinterpret_cast<SOCKADDR *>(&clientAddr),
                              &clientAddrSize);
        if (recvResult == SOCKET_ERROR) {
            std::cerr << "recvfrom failed with error " << WSAGetLastError() << std::endl;
            break;
        }

        // 处理接收到的数据
        handle(buffer, recvResult);
        std::cout << "Received data from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port)
                  << ": " << buffer << std::endl;
    }

    // 关闭套接字和清理Winsock
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
