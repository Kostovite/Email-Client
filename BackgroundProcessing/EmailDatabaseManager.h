#pragma once

#include "../ShareComponents/Email.h"

#include "sqlite/sqlite3.h"
#include <vector>
#include <string>

using std::vector, std::string;

class EmailDatabaseManager {
private:
    sqlite3* _database;
    string _databasePath;
    bool _executeQuery(const string& query);

public:
    EmailDatabaseManager();
	~EmailDatabaseManager();

public:
};