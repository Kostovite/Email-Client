#include "pch.h"
#include "SMTP_Client.h"
#include "rtf_Mime.h"

SMTP_Client::SMTP_Client() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // Handle the error as needed
    }
	_socket = socket(AF_INET, SOCK_STREAM, 0);
    _server = "192.168.1.174"; //Currently set to my local IP address
    _port = 2500;
	if (_socket == INVALID_SOCKET) {
		WSACleanup();
	}
}

SMTP_Client::SMTP_Client(std::string server, int32_t port) {
	_server = server;
	_port = port;
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		// Handle the error as needed
	}
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET) {
		WSACleanup();
	}
}

SMTP_Client::~SMTP_Client() {
    closesocket(_socket);
    WSACleanup();
}

std::tuple<bool, std::string> SMTP_Client::sendEmail(const std::string& sender, const std::string& recipient, const std::string bcc, const std::string& subject, const std::string& content)
{
    // Specify the SMTP server address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(_server.c_str());
    serverAddress.sin_port = htons(_port);

    // Connect to the SMTP server
    if (connect(_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        closesocket(_socket);
        WSACleanup();
        return std::make_tuple(false, "Failed to connect to the SMTP server");
    }

    // Receive the server response
    char serverResponse[1024];
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
		return std::make_tuple(false, "Failed to connect to the SMTP server");
	}

    // SMTP Handshake (EHLO)
    std::string ehloCommand = "EHLO client\r\n";
    send(_socket, ehloCommand.c_str(), ehloCommand.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
        closesocket(_socket);
        WSACleanup();
        return std::make_tuple(false, "Failed to connect to the SMTP server");
    }

    // Set Sender (MAIL FROM)
    std::string mailFromCommand = "MAIL FROM: <" + sender + ">\r\n";
    send(_socket, mailFromCommand.c_str(), mailFromCommand.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
		closesocket(_socket);
		WSACleanup();
		return std::make_tuple(false, "Failed to connect to the SMTP server");
	}

    // Set Recipient (RCPT TO)
    std::string rcptToCommand = "RCPT TO: <" + recipient + ">\r\n";
    send(_socket, rcptToCommand.c_str(), rcptToCommand.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
        closesocket(_socket);
        WSACleanup();
        return std::make_tuple(false, "Failed to connect to the SMTP server");
    }

    // Start Email Data (DATA)
    std::string dataCommand = "DATA\r\n";
    send(_socket, dataCommand.c_str(), dataCommand.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '3') {
		closesocket(_socket);
		WSACleanup();
		return std::make_tuple(false, "Failed to connect to the SMTP server");
	}

    // Compose and Send Email Content
    base64::encode(content.c_str(), content.length());
    Convert::Convertor convertor;
    std::string emailContent = ("Subject: " + convertor.rtfToMime(subject) + "\r\n\r\n" + content + "\r\n.\r\n").c_str();
    send(_socket, emailContent.c_str(), emailContent.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
		closesocket(_socket);
		WSACleanup();
		return std::make_tuple(false, "Failed to connect to the SMTP server");
	}

    // Quit (QUIT)
    std::string quitCommand = "QUIT\r\n";
    send(_socket, quitCommand.c_str(), quitCommand.length(), 0);

    // Receive the server response
    recv(_socket, serverResponse, sizeof(serverResponse), 0);

    if (serverResponse[0] != '2') {
        closesocket(_socket);
        WSACleanup();
        return std::make_tuple(false, "Failed to receive end respond from the SMTP server");
    }

    return std::make_tuple(true, "Email sent successfully");
}