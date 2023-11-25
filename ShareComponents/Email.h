#pragma once

#include <iostream>
#include <string>

using std::cin, std::cout, std::endl, std::getline, std::string;

class Email {
private:
    int _id;
    string _sender;
    string _recipient;
    string _subject;
    string _content;
    string _timestamp;

public:
    Email();
    Email(int id, const string& sender, const string& recipient, const string& subject, const string& content, const string& timestamp);
    ~Email();

public:
    int getId() const;
    const string& getSender() const;
    const string& getRecipient() const;
    const string& getSubject() const;
    const string& getContent() const;
    const string& getTimestamp() const;

    void setId(int id);
    void setSender(const string& sender);
    void setRecipient(const string& recipient);
    void setSubject(const string& subject);
    void setContent(const string& content);
    void setTimestamp(const string& timestamp);

public:
    string emailQuery() const;
};