#include "pch.h"
#include "POP3_Client.h"
#include "rtf_Mime.h"

POP3_Client::POP3_Client() : _port(1100) {}  // Default POP3 port

POP3_Client::POP3_Client(std::string server, int32_t port, std::string username, std::string password)
    : _server(server), _port(port), _username(username), _password(password) {}

POP3_Client::~POP3_Client() {
    closesocket(_socket);
    WSACleanup();
}

// Helper function to extract header values
std::string POP3_Client::extractHeaderValue(const std::string& emailContent, const std::string& header)
{
    size_t pos = emailContent.find(header);
    if (pos != std::string::npos) {
        pos += header.length();
        size_t end = emailContent.find("\r\n", pos);
        if (end != std::string::npos) {
            return emailContent.substr(pos, end - pos);
        }
    }
    return "";
}

std::tuple<bool, std::string> POP3_Client::receiveEmail(std::string& sender, std::string& recipient, std::string& subject, std::string& content)
{
    // Initialize WinSock
    WSAData wsaData;
    WORD version = MAKEWORD(2, 2);
    int32_t wsResult = WSAStartup(version, &wsaData);
    if (wsResult != 0) {
        std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
        return std::make_tuple(false, "Can't start Winsock");
    }

    // Create socket
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET) {
        std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
        return std::make_tuple(false, "Can't create socket");
    }

    // Fill in a hint structure
    sockaddr_in hint{};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(_port);
    inet_pton(AF_INET, _server.c_str(), &hint.sin_addr);

    // Connect to server
    int32_t connResult = connect(_socket, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
        return std::make_tuple(false, "Can't connect to server");
    }
    char buf[4096];
    std::string command;
    int32_t sendResult;
    int32_t bytesReceived;

    //Send CAPA command
    command = "CAPA\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
		return std::make_tuple(false, "Can't send CAPA command");
	}

    // Receive response for CAPA command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
		return std::make_tuple(false, "Error receiving response for CAPA command");
	}

    // Send USER command
    command = "USER " + _username + "\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
        return std::make_tuple(false, "Can't send USER command");
    }

    // Receive response for USER command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
        return std::make_tuple(false, "Error receiving response for USER command");
    }

    // Send PASS command
    command = "PASS " + _password + "\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
		return std::make_tuple(false, "Can't send PASS command");
	}

    //Receive response for PASS command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
        return std::make_tuple(false, "Error receiving response for PASS command");
    }

    // Send TOP command to get the header of the first email
    command = "TOP 1 0\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
		return std::make_tuple(false, "Can't send TOP command");
	}

    // Receive response for TOP command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
		return std::make_tuple(false, "Error receiving response for TOP command");
	}

    // Extract the email header
    std::string emailHeader(buf, bytesReceived);
    
    // Extract the sender
    sender = extractHeaderValue(emailHeader, "From: ");

    // Extract the recipient
    recipient = extractHeaderValue(emailHeader, "To: ");

    // Extract the subject
    subject = extractHeaderValue(emailHeader, "Subject: ");

    // Send RETR command to get the content of the first email
    command = "RETR 1\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
        return std::make_tuple(false, "Can't send RETR command");
    }

    // Receive response for RETR command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
		return std::make_tuple(false, "Error receiving response for RETR command");
	}

    // Extract the email content
    std::string emailContent(buf, bytesReceived);

    // Extract the MIME content
    std::string mimeContent = extractHeaderValue(emailContent, "\r\n\r\n");

    return std::make_tuple(true, "Success");
}