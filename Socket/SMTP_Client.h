#pragma once

#ifdef SMTP_CLIENT_EXPORTS
#define SMTP_CLIENT_API __declspec(dllexport)
#else
#define SMTP_CLIENT_API __declspec(dllimport)
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

extern "C" SMTP_CLIENT_API class SMTP_Client
{
private:
	SOCKET _socket;
public:
	__declspec(dllexport) SMTP_Client();
	__declspec(dllexport) ~SMTP_Client();
	__declspec(dllexport) bool ConnectToServer(std::string server, int32_t port);
};