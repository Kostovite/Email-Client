#include "EmailDatabaseManager.h"
#include <iostream>

using std::cout, std::endl;

bool EmailDatabaseManager::_executeQuery(const string& query)
{
    char* errorMessage = nullptr;
    int result = sqlite3_exec(_database, query.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        cout << "Error executing query: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

EmailDatabaseManager::EmailDatabaseManager()
{
    _databasePath = "EmailDatabase.db";
    int result = sqlite3_open(_databasePath.c_str(), &_database);
    if (result != SQLITE_OK) {
        cout << "Error opening database: " << sqlite3_errmsg(_database) << endl;
    }
    else {
        cout << "Database opened successfully" << endl;
    }
}

EmailDatabaseManager::~EmailDatabaseManager()
{
    sqlite3_close(_database);
}

