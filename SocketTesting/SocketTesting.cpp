#include <iostream>
#include <string>

#include "POP3_Client.h"
#include "SMTP_Client.h"

int main() {
	POP3_Client pop3Client("192.168.1.174", 1100, USER, PASSWORD);
	std::vector<std::string> sender, recipient, subject, content;
	pop3Client.receiveEmail(sender, recipient, subject, content);
}
