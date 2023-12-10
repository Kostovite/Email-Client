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
#include <tuple>
#include "../Components/cppcodec/base64_default_rfc4648.hpp"

extern "C" SMTP_CLIENT_API class SMTP_Client
{
private:
    SOCKET _socket{};
    std::string _server;  // Remove the reference here
    int32_t _port{};

public:
	__declspec(dllexport) SMTP_Client();
	__declspec(dllexport) SMTP_Client(std::string server, int32_t port);
	__declspec(dllexport) ~SMTP_Client();

public:
	__declspec(dllexport) std::tuple<bool, std::string> sendEmail(const std::string& sender, const std::string& recipient,
		const std::string bcc, const std::string& subject, const std::string& content);
};