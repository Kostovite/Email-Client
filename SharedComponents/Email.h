#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Date.h"

using std::cin, std::cout, std::endl, std::getline, std::string, std::vector;

class Email {
private:
	string _sender;
	vector<string> _recipientsCC;
	vector<string> _recipientsBCC;
	string _subject;
	string _body;
	Date _date;
public:
	Email();
	Email(string sender, vector<string> recipientsCC, vector<string> recipientsBCC, string subject, string body, Date date);
	~Email();
	string getSender();
	vector<string> getRecipientsCC();
	vector<string> getRecipientsBCC();
	string getSubject();
	string getBody();
	void setSender(string sender);
	void setRecipientsCC(vector<string> recipientsCC);
	void setRecipientsBCC(vector<string> recipientsBCC);
	void setSubject(string subject);
	void setBody(string body);
};