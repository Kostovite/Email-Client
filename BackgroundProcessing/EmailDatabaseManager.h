#pragma once

#include "../ShareComponents/Email.h"

#include "sqlite/sqlite3.h"
#include <vector>
#include <string>

using std::vector, std::string;

class EmailDatabaseManager {
protected:
    sqlite3* _database;
    string _databasePath;
    bool _executeQuery(const string& query);

public:
    EmailDatabaseManager();
	~EmailDatabaseManager();

    const string TABLE_NAMES[4] = { "inbox", "sent", "drafts", "trash" };

public:
    virtual bool initializeDatabase();

    virtual bool addEmailTo(const Email& email, const string& tableName);
    virtual vector<Email> getEmailsFrom(const string& tableName);
    virtual void removeAllEmailsIn(const string& tableName);
    virtual bool moveEmailBetween(const Email& email, const string& fromTableName, const string& toTableName);
    virtual bool moveAllToTrash(const string& fromTableName);
};