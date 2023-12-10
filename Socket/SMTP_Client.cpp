#include "pch.h"
#include "SMTP_Client.h"
#include "rtf_Mime.h"
#include "../Components/cppcodec/base64_default_rfc4648.hpp"

#include <random>
#include <WS2tcpip.h>

SMTP_Client::SMTP_Client() {
    _server = "192.168.1.174";
    _port = 2500;
}

SMTP_Client::SMTP_Client(std::string server, int32_t port) {
	_server = server;
	_port = port;
	
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // Handle the error as needed
    }

    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socket == INVALID_SOCKET) {
        // Handle socket creation failure
        WSACleanup();
        // Optionally throw an exception or return from the constructor
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);

    if (inet_pton(AF_INET, _server.c_str(), &serverAddr.sin_addr) <= 0) {
        // Handle address conversion failure
        closesocket(_socket);
        WSACleanup();
        // Optionally throw an exception or return from the constructor
    }

    if (connect(_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        // Handle connection failure
        closesocket(_socket);
        WSACleanup();
        // Optionally throw an exception or return from the constructor
    }

    char serverResponse[1024];
    recv(_socket, serverResponse, sizeof(serverResponse), 0);
}

SMTP_Client::~SMTP_Client() {
}

std::string SMTP_Client::buildHeader(const std::string& sender, const std::string& recipient, const std::string& subject)
{
    std::stringstream headers;
    //Message-ID
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::string messageID = "<";
    for (int i = 0; i < 10; i++) {
		messageID += std::to_string(dis(gen));
	}
    messageID += "@";
    for (int i = 0; i < 10; i++) {
        messageID += std::to_string(dis(gen));
    }
    messageID += ">";
    headers << "Message-ID: " << messageID << "\r\n";

    //Date
    std::time_t t = std::time(nullptr);
    //Using localtime_s instead of localtime to avoid warning C4996
    struct tm localTime;
    localtime_s(&localTime, &t);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %z", &localTime);
    headers << "Date: " << buffer << "\r\n";

    //MIME-Version
    headers << "MIME-Version: 1.0\r\n";

    //Content-Language
    headers << "Content-Language: vi-VN\r\n";

    //To
    headers << "To: " << recipient << "\r\n";

    //From
    headers << "From: " << sender << "\r\n";

    //Subject
    headers << "Subject: " << subject << "\r\n";

    return headers.str();
}

std::string SMTP_Client::buildBody(const std::string& content) {
    std::stringstream body;
    body << "Content-Type: text/rtf; charset=UTF-8\r\n";
    body << "\r\n";
    body << content;
    body << "\r\n.\r\n"; // Required for message termination
    return body.str();
}

std::string SMTP_Client::base64EncodeFile(const std::string& filename)
{
    return std::string();
}

void SMTP_Client::endSession()
{
    std::string quitCommand = "QUIT\r\n";
	send(_socket, quitCommand.c_str(), quitCommand.length(), 0);
	closesocket(_socket);
	WSACleanup();
}

std::tuple<bool, std::string> SMTP_Client::sendEmail(const std::string& sender, const std::string& recipient, const std::string bcc, const std::string& subject, const std::string& content)
{
    char serverResponse[1024];

    // SMTP Handshake (EHLO)
    std::string ehloCommand = "EHLO [" + _server + "] \r\n";
    send(_socket, ehloCommand.c_str(), ehloCommand.length(), 0);
    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
        return std::make_tuple(false, "Failed to connect to the SMTP server");
    }

    // Set Sender (MAIL FROM)
    std::string mailFromCommand = "MAIL FROM: <" + sender + ">\r\n";
    send(_socket, mailFromCommand.c_str(), mailFromCommand.length(), 0);
    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
		return std::make_tuple(false, "Failed to connect to the SMTP server");
	}

    // Set Recipient (RCPT TO)
    std::string rcptToCommand = "RCPT TO: <" + recipient + ">\r\n";
    send(_socket, rcptToCommand.c_str(), rcptToCommand.length(), 0);
    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
        return std::make_tuple(false, "Failed to connect to the SMTP server");
    }

    // Start Email Data (DATA)
    std::string dataCommand = "DATA\r\n";
    send(_socket, dataCommand.c_str(), dataCommand.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '3') {
        return std::make_tuple(false, "Failed to connect to the SMTP server");
    }

    std::string emailContent = buildHeader(sender, recipient, subject) + buildBody(content);

    // Send Email Content
    send(_socket, emailContent.c_str(), emailContent.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    return std::make_tuple(true, "Email sent successfully");
}