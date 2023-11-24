#pragma once

// ConsoleApp/EmailDatabaseManager.h
#pragma once

#include "../SharedComponents/Email.h"

#include <sqlite3.h>
#include <vector>

using std::vector;

class EmailDatabaseManager {
private:
public:
    EmailDatabaseManager();
    ~EmailDatabaseManager();

    // CRUD operations
    bool addEmail(const Email& email);
    bool updateEmail(const Email& email);
    bool deleteEmail(int emailId);
    Email getEmailById(int emailId);
    std::vector<Email> getAllEmails();
};