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
        throw sqlite3_errmsg(_database);
    }
}

EmailDatabaseManager::~EmailDatabaseManager()
{
    sqlite3_close(_database);
}

bool EmailDatabaseManager::initializeDatabase()
{
	//Initialize the database with given table array
	for (int i = 0; i < sizeof(TABLE_NAMES) / sizeof(TABLE_NAMES[0]); i++) {
		string query = "CREATE TABLE IF NOT EXISTS " + TABLE_NAMES[i] + " (id INTEGER PRIMARY KEY AUTOINCREMENT, sender TEXT NOT NULL, recipient TEXT NOT NULL, subject TEXT NOT NULL, content TEXT NOT NULL, timestamp TEXT NOT NULL, type TEXT NOT NULL);";
		if (!_executeQuery(query)) {
			return false;
		}
	}
	return true;
}

bool EmailDatabaseManager::addEmailTo(const Email& email, const string& tableName)
{
    string query = "INSERT INTO " + tableName + " (sender, recipient, subject, content, timestamp, type) VALUES ('" + email.getSender() + "', '" + email.getRecipient() + "', '" + email.getSubject() + "', '" + email.getContent() + "', '" + email.getTimestamp() + "', '" + email.getType() + "');";
	return _executeQuery(query);
}

vector<Email> EmailDatabaseManager::getEmailsFrom(const string& tableName)
{
	vector<Email> emails;
	string query = "SELECT * FROM " + tableName + ";";
	sqlite3_stmt* statement;
	int result = sqlite3_prepare_v2(_database, query.c_str(), -1, &statement, nullptr);
    if (result != SQLITE_OK) {
		cout << "Error preparing statement: " << sqlite3_errmsg(_database) << endl;
	}
    else {
        while (sqlite3_step(statement) == SQLITE_ROW) {
			int id = sqlite3_column_int(statement, 0);
			string sender = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			string recipient = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			string subject = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			string content = reinterpret_cast<const char*>(sqlite3_column_text(statement, 4));
			string timestamp = reinterpret_cast<const char*>(sqlite3_column_text(statement, 5));
			string type = reinterpret_cast<const char*>(sqlite3_column_text(statement, 6));
			emails.push_back(Email(id, sender, recipient, subject, content, timestamp, type));
		}
	}
	sqlite3_finalize(statement);
	return emails;
}

void EmailDatabaseManager::removeAllEmailsIn(const string& tableName)
{
	string query = "DELETE FROM " + tableName + ";";
	_executeQuery(query);
}

bool EmailDatabaseManager::moveEmailBetween(const Email& email, const string& fromTableName, const string& toTableName)
{
    // Insert the email into the destination table
    string insertQuery = "INSERT INTO " + toTableName + " (sender, recipient, subject, content, timestamp, type) VALUES ('" + email.getSender() + "', '" + email.getRecipient() + "', '" + email.getSubject() + "', '" + email.getContent() + "', '" + email.getTimestamp() + "', '" + email.getType() + "');";

    if (!_executeQuery(insertQuery)) {
        return false;  // Insert failed
    }

    // Retrieve the last inserted ID in the destination table
    string lastIdQuery = "SELECT last_insert_rowid();";
    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(_database, lastIdQuery.c_str(), -1, &statement, nullptr);

    if (result != SQLITE_OK) {
        cout << "Error preparing statement: " << sqlite3_errmsg(_database) << endl;
        return false;
    }

    int newId = 0;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        newId = sqlite3_column_int(statement, 0);
    }

    // Finalize the statement
    sqlite3_finalize(statement);

    // Delete the email from the source table using the new ID
    string deleteQuery = "DELETE FROM " + fromTableName + " WHERE id = " + std::to_string(newId) + ";";
    return _executeQuery(deleteQuery);
}

bool EmailDatabaseManager::moveAllToTrash(const string& fromTableName)
{
    // Get all emails from the source table
	vector<Email> emails = getEmailsFrom(fromTableName);

    //Reset the source table sequence
    string resetSequenceQuery = "DELETE FROM sqlite_sequence WHERE name = '" + fromTableName + "';";
    if (!_executeQuery(resetSequenceQuery)) {
	    return false;
    }
	// Move each email to the trash table
	for (Email email : emails) {
		if (!moveEmailBetween(email, fromTableName, "Trash")) {
			return false;
		}
	}
	return true;
}

