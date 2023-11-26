#include "Email.h"

Email::Email()
{
	_id = -1;
	_sender = "";
	_recipient = "";
	_subject = "";
	_content = "";
	_timestamp = "";
	_type = "";
}

Email::Email(int id, const string& sender, const string& recipient, const string& subject, const string& content, const string& timestamp, const string& type)
{
	_id = id;
	_sender = sender;
	_recipient = recipient;
	_subject = subject;
	_content = content;
	_timestamp = timestamp;
	_type = type;
}

Email::~Email()
{

}

int Email::getId() const
{
	return _id;
}

const string& Email::getSender() const
{
	return _sender;
}

const string& Email::getRecipient() const
{
	return _recipient;
}

const string& Email::getSubject() const
{
	return _subject;
}

const string& Email::getContent() const
{
	return _content;
}

const string& Email::getTimestamp() const
{
	return _timestamp;
}

const string& Email::getType() const
{
	return _type;
}

void Email::setId(int id)
{
	_id = id;
}

void Email::setSender(const string& sender)
{
	_sender = sender;
}

void Email::setRecipient(const string& recipient)
{
	_recipient = recipient;
}

void Email::setSubject(const string& subject)
{
	_subject = subject;
}

void Email::setContent(const string& content)
{
	_content = content;
}

void Email::setTimestamp(const string& timestamp)
{
	_timestamp = timestamp;
}

void Email::setType(const string& type)
{
	_type = type;
}