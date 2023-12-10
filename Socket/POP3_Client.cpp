#include "pch.h"
#include "POP3_Client.h"
#include "rtf_Mime.h"

POP3_Client::POP3_Client() {
    _server = "192.168.1.174";
    _port = 1100;
    _username = USER;
    _password = PASSWORD;
}  

POP3_Client::POP3_Client(std::string server, int32_t port, std::string username, std::string password)
    : _server(server), _port(port), _username(username), _password(password) {

    // Initialize WinSock
    WSAData wsaData;
    WORD version = MAKEWORD(2, 2);
    int32_t wsResult = WSAStartup(version, &wsaData);

    // Create socket
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    // Fill in a hint structure
    sockaddr_in hint{};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(_port);
    inet_pton(AF_INET, _server.c_str(), &hint.sin_addr);

    // Connect to server
    int32_t connResult = connect(_socket, (sockaddr*)&hint, sizeof(hint));

    char buf[4096];

    //Receive greeting message from server
    ZeroMemory(buf, sizeof(buf));
    int32_t bytesReceived = recv(_socket, buf, sizeof(buf), 0);
}

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

std::string POP3_Client::extractMimeContent(const std::string& emailContent) {
    size_t start = emailContent.find("\r\n\r\n") + 4;  // Start of MIME content
    return emailContent.substr(start);
}

std::tuple<bool, std::string> POP3_Client::receiveEmail(std::vector<std::string>& sender, std::vector<std::string>& recipient, std::vector<std::string>& subject, std::vector<std::string>& content)
{
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

    // Check if USER command was successful (response should start with +OK)
    if (strncmp(buf, "+OK", 3) != 0) {
        return std::make_tuple(false, "USER command failed");
    }

    // Send PASS command
    command = "PASS " + _password + "\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
        return std::make_tuple(false, "Can't send PASS command");
    }

    // Receive response for PASS command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
        return std::make_tuple(false, "Error receiving response for PASS command");
    }

    // Check if PASS command was successful (response should start with +OK)
    if (strncmp(buf, "+OK", 3) != 0) {
        return std::make_tuple(false, "PASS command failed");
    }

    //Send STAT command
    command = "STAT\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
        return std::make_tuple(false, "Can't send STAT command");
    }

    // Receive response for STAT command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
        return std::make_tuple(false, "Error receiving response for STAT command");
    }

    // Check if STAT command was successful (response should start with +OK)
    if (strncmp(buf, "+OK", 3) != 0) {
        return std::make_tuple(false, "STAT command failed");
    }

    std::tuple<int32_t, int32_t> emailStat;
    //Get the number of emails on the server with format "+OK %d %d"
    sscanf_s(buf, "+OK %d %d", &std::get<0>(emailStat), &std::get<1>(emailStat));

    //Send LIST command
    command = "LIST\r\n";
    sendResult = send(_socket, command.c_str(), command.size(), 0);
    if (sendResult == SOCKET_ERROR) {
        return std::make_tuple(false, "Can't send LIST command");
    }

    // Receive response for LIST command
    ZeroMemory(buf, sizeof(buf));
    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
    if (bytesReceived == SOCKET_ERROR) {
        return std::make_tuple(false, "Error receiving response for LIST command");
    }

    //Get the number of emails on the server with format "+OK \n %d %d \n..." (first line is "+OK", emailStat<0> line later is %d %d)
    std::vector<std::tuple<int32_t, int32_t>> emailList;
    std::istringstream iss(buf);
    std::string line;
    //Skip the first line
    std::getline(iss, line);
    //Get the rest of the lines
    for (int ind = 0; ind < std::get<0>(emailStat); ind++) {
        std::getline(iss, line);
        std::tuple<int32_t, int32_t> email;
        sscanf_s(line.c_str(), "%d %d", &std::get<0>(email), &std::get<1>(email));
        emailList.push_back(email);
    }

    //Send RETR command for every email in the list
    for (int32_t i = 0; i < std::get<0>(emailStat); i++) {

        //Send RETR command
        command = "RETR " + std::to_string(std::get<0>(emailList[i])) + "\r\n";
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

        //Buf format
        //+OK %d
        //Message-ID: <%s>
        //Date: %s
        //MIME-Version: 1.0
        //Content-Language: %s
        //To: %s
        //From: %s
        //Subject: %s
        //Content-Type: text/rtf; charset=UTF-8
        //
        //
        //Subject: %s
        //.

        //Get recipient
        std::istringstream iss(buf);
        //Skip 5 lines
        for (int ind = 0; ind < 5; ind++) {
			std::getline(iss, line);
		}

        std::string pushStr;

        //Get recipient after "To: "
        std::getline(iss, line);
        pushStr = line.substr(4);
        pushStr.pop_back();
        recipient.push_back(pushStr);

        //Get sender after "From: "
        std::getline(iss, line);
        pushStr = line.substr(6);
        pushStr.pop_back();
        sender.push_back(pushStr);

        //Get subject after "Subject: "
        std::getline(iss, line);
        pushStr = line.substr(9);
        pushStr.pop_back();
        subject.push_back(pushStr);

        //Get content after "\r\n\r\n"
        std::getline(iss, line);
        std::getline(iss, line);

        //Get content until "."
        std::string contentStr;
        while (line != ".\r") {
			contentStr += line + "\r\n";
			std::getline(iss, line);
		}
        content.push_back(contentStr);
    }

    return std::make_tuple(true, "Success");
}



//std::tuple<bool, std::string> POP3_Client::receiveEmail(std::string& sender, std::string& recipient, std::string& subject, std::string& content)
//{
//    // Initialize WinSock
//    WSAData wsaData;
//    WORD version = MAKEWORD(2, 2);
//    int32_t wsResult = WSAStartup(version, &wsaData);
//    if (wsResult != 0) {
//        std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
//        return std::make_tuple(false, "Can't start Winsock");
//    }
//
//    // Create socket
//    _socket = socket(AF_INET, SOCK_STREAM, 0);
//    if (_socket == INVALID_SOCKET) {
//        std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
//        return std::make_tuple(false, "Can't create socket");
//    }
//
//    // Fill in a hint structure
//    sockaddr_in hint{};
//    hint.sin_family = AF_INET;
//    hint.sin_port = htons(_port);
//    inet_pton(AF_INET, _server.c_str(), &hint.sin_addr);
//
//    // Connect to server
//    int32_t connResult = connect(_socket, (sockaddr*)&hint, sizeof(hint));
//    if (connResult == SOCKET_ERROR) {
//        std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
//        return std::make_tuple(false, "Can't connect to server");
//    }
//    char buf[4096];
//    std::string command;
//    int32_t sendResult;
//    int32_t bytesReceived;
//
//    //Receive greeting message from server
//    ZeroMemory(buf, sizeof(buf));
//    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
//    if (bytesReceived == SOCKET_ERROR) {
//		return std::make_tuple(false, "Error receiving greeting message from server");
//	}
//
//    //Send CAPA command
//    command = "CAPA\r\n";
//    sendResult = send(_socket, command.c_str(), command.size(), 0);
//    if (sendResult == SOCKET_ERROR) {
//		return std::make_tuple(false, "Can't send CAPA command");
//	}
//
//    // Receive response for CAPA command
//    ZeroMemory(buf, sizeof(buf));
//    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
//    if (bytesReceived == SOCKET_ERROR) {
//		return std::make_tuple(false, "Error receiving response for CAPA command");
//	}
//
//    // Send USER command
//    command = "USER " + _username + "\r\n";
//    sendResult = send(_socket, command.c_str(), command.size(), 0);
//    if (sendResult == SOCKET_ERROR) {
//        return std::make_tuple(false, "Can't send USER command");
//    }
//
//    // Receive response for USER command
//    ZeroMemory(buf, sizeof(buf));
//    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
//    if (bytesReceived == SOCKET_ERROR) {
//        return std::make_tuple(false, "Error receiving response for USER command");
//    }
//
//    // Check if USER command was successful (response should start with +OK)
//    if (strncmp(buf, "+OK", 3) != 0) {
//        return std::make_tuple(false, "USER command failed");
//    }
//
//    // Send PASS command
//    command = "PASS " + _password + "\r\n";
//    sendResult = send(_socket, command.c_str(), command.size(), 0);
//    if (sendResult == SOCKET_ERROR) {
//        return std::make_tuple(false, "Can't send PASS command");
//    }
//
//    // Receive response for PASS command
//    ZeroMemory(buf, sizeof(buf));
//    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
//    if (bytesReceived == SOCKET_ERROR) {
//        return std::make_tuple(false, "Error receiving response for PASS command");
//    }
//
//    // Check if PASS command was successful (response should start with +OK)
//    if (strncmp(buf, "+OK", 3) != 0) {
//        return std::make_tuple(false, "PASS command failed");
//    }
//
//    //Send STAT command
//    command = "STAT\r\n";
//    sendResult = send(_socket, command.c_str(), command.size(), 0);
//    if (sendResult == SOCKET_ERROR) {
//		return std::make_tuple(false, "Can't send STAT command");
//	}
//
//    // Receive response for STAT command
//    ZeroMemory(buf, sizeof(buf));
//    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
//    if (bytesReceived == SOCKET_ERROR) {
//        return std::make_tuple(false, "Error receiving response for STAT command");
//    }
//
//    // Check if STAT command was successful (response should start with +OK)
//    if (strncmp(buf, "+OK", 3) != 0) {
//		return std::make_tuple(false, "STAT command failed");
//	}
//
//    std::tuple<int32_t, int32_t> emailStat;
//    //Get the number of emails on the server with format "+OK %d %d"
//    sscanf_s(buf, "+OK %d %d", &std::get<0>(emailStat), &std::get<1>(emailStat));
//
//    //Send LIST command
//    command = "LIST\r\n";
//    sendResult = send(_socket, command.c_str(), command.size(), 0);
//    if (sendResult == SOCKET_ERROR) {
//        return std::make_tuple(false, "Can't send LIST command");
//    }
//
//    // Receive response for LIST command
//    ZeroMemory(buf, sizeof(buf));
//    bytesReceived = recv(_socket, buf, sizeof(buf), 0);
//    if (bytesReceived == SOCKET_ERROR) {
//		return std::make_tuple(false, "Error receiving response for LIST command");
//	}
//
//    std::cout << buf << std::endl;
//    //Get the number of emails on the server with format "+OK \n %d %d \n..." (first line is "+OK", emailStat<0> line later is %d %d)
//    std::vector<std::tuple<int32_t, int32_t>> emailList;
//    std::istringstream iss(buf);
//    std::string line;
//    //Skip the first line
//    std::getline(iss, line);
//    //Get the rest of the lines
//    for (int ind = 0; ind < std::get<0>(emailStat); ind++) {
//        std::getline(iss, line);
//		std::tuple<int32_t, int32_t> email;
//		sscanf_s(line.c_str(), "%d %d", &std::get<0>(email), &std::get<1>(email));
//		emailList.push_back(email);
//	}
//
//    //Send RETR command for every email in the list
//    for (int32_t i = 0; i < std::get<0>(emailStat); i++) {
//
//        //Send RETR command
//        command = "RETR " + std::to_string(std::get<0>(emailList[i])) + "\r\n";
//        sendResult = send(_socket, command.c_str(), command.size(), 0);
//        if (sendResult == SOCKET_ERROR) {
//			return std::make_tuple(false, "Can't send RETR command");
//		}
//
//        // Receive response for RETR command
//        ZeroMemory(buf, sizeof(buf));
//        bytesReceived = recv(_socket, buf, sizeof(buf), 0);
//        if (bytesReceived == SOCKET_ERROR) {
//            return std::make_tuple(false, "Error receiving response for RETR command");
//        }
//
//        std::cout << buf << std::endl;
//	}
//    
//    
//
//    return std::make_tuple(true, "Success");
//}