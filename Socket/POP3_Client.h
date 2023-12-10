#pragma once

#ifdef POP3_CLIENT_EXPORTS
#define POP3_CLIENT_API __declspec(dllexport)
#else
#define POP3_CLIENT_API __declspec(dllimport)
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <tuple>
#include "../Components/cppcodec/base64_default_rfc4648.hpp"

#define SERVER "pop.gmail.com"
#define PORT 995
#define USER "minhhieudo2545@gmail.com"
#define PASSWORD "170704Aa"

extern "C" POP3_CLIENT_API class POP3_Client
{
private:
	SOCKET _socket{};
	std::string _server;  // Remove the reference here
	int32_t _port{};
	std::string _username;
	std::string _password;

public:
	__declspec(dllexport) POP3_Client();
	__declspec(dllexport) POP3_Client(std::string server, int32_t port, std::string username, std::string password);
	__declspec(dllexport) ~POP3_Client();

	std::string extractHeaderValue(const std::string& emailContent, const std::string& header);
	__declspec(dllexport) std::tuple<bool, std::string> receiveEmail(std::string& sender, std::string& recipient, std::string& subject, std::string& content);
};