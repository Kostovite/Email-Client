#pragma once

#include "../ShareComponents/Email.h"

#include "sqlite/sqlite3.h"
#include <vector>
#include <string>

using std::vector, std::string;

//Define a tableName types array for the database
const string TABLE_NAMES[] = { "inbox", "sent", "drafts", "trash" };

class EmailDatabaseManager {
protected:
    sqlite3* _database;
    string _databasePath;
    bool _executeQuery(const string& query);

public:
    EmailDatabaseManager();
	~EmailDatabaseManager();

public:
    bool initializeDatabase();

    bool addEmailTo(const Email& email, const string& tableName);
    vector<Email> getEmailsFrom(const string& tableName);
    void removeAllEmailsIn(const string& tableName);
    bool moveEmailBetween(const Email& email, const string& fromTableName, const string& toTableName);
    bool moveAllToTrash(const string& fromTableName);
};