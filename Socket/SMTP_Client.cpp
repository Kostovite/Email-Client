#include "pch.h"
#include "SMTP_Client.h"

SMTP_Client::SMTP_Client() {
    WSADATA wsaData;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET) {
        WSACleanup();
    }
}

SMTP_Client::~SMTP_Client() {
    closesocket(_socket);
    WSACleanup();
}

bool SMTP_Client::ConnectToServer(std::string server, int32_t port) {
    // Specify the server address and port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(server.c_str());
    serverAddr.sin_port = htons(port);
    if (connect(_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        return false;
    }
    return true;
}