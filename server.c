#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main() {
	
    WSADATA wsaData;
    SOCKET serverSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    char buffer[1024] = { 0 };
    int iResult;
    
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("error : %d\n", iResult);
        return 1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        printf("socket error %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);
    

    iResult = bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (iResult == SOCKET_ERROR) {
        printf("Bind ERROR: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    iResult = listen(serverSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("Listen error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    printf("127.0.0.1:%d waiting..\n", PORT);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        printf("Accept error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        printf("message: %s\n", buffer);
        
        char* reply = "Success!\n";
        send(clientSocket, reply, (int)strlen(reply), 0);
    }
    

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();



}
