#include "../EmailUI/pch.h"
#include "Email.h"

Email::Email()
{

}

Email::Email(string sender, vector<string> recipientsCC, vector<string> recipientsBCC, string subject, string body, Date date)
{
	this->_sender = sender;
	this->_recipientsCC = recipientsCC;
	this->_recipientsBCC = recipientsBCC;
	this->_subject = subject;
	this->_body = body;
	this->_date = date;
}

Email::~Email()
{

}

string Email::getSender()
{
	return this->_sender;
}

vector<string> Email::getRecipientsCC()
{
	return this->_recipientsCC;
}

vector<string> Email::getRecipientsBCC()
{
	return this->_recipientsBCC;
}

string Email::getSubject()
{
	return this->_subject;
}

string Email::getBody()
{
	return this->_body;
}

void Email::setSender(string sender)
{
	this->_sender = sender;
}

void Email::setRecipientsCC(vector<string> recipientsCC)
{
	this->_recipientsCC = recipientsCC;
}

void Email::setRecipientsBCC(vector<string> recipientsBCC)
{
	this->_recipientsBCC = recipientsBCC;
}

void Email::setSubject(string subject)
{
	this->_subject = subject;
}

void Email::setBody(string body)
{
	this->_body = body;
}