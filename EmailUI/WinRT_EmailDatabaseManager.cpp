#include "pch.h"
#include "WinRT_EmailDatabaseManager.h"
#if __has_include("WinRT_EmailDatabaseManager.g.cpp")
#include "WinRT_EmailDatabaseManager.g.cpp"
#endif

#include "winrt/Windows.Storage.h"
#include "Email.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation::Collections;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    bool WinRT_EmailDatabaseManager::_executeQuery(const hstring& query)
    {
        char* errorMessage = nullptr;
        int result = sqlite3_exec(_database, to_string(query).c_str(), nullptr, nullptr, &errorMessage);
        if (result != SQLITE_OK) {
            sqlite3_free(errorMessage);
            return false;
        }
        return true;
    }

    WinRT_EmailDatabaseManager::WinRT_EmailDatabaseManager()
    {
        _databasePath = L"EmailDatabase.db";
        //Get local folder
        Windows::Storage::StorageFolder localFolder = Windows::Storage::ApplicationData::Current().LocalFolder();
        _databasePath = localFolder.Path() + L"\\" + _databasePath;
        
        int32_t result = sqlite3_open(to_string(_databasePath).c_str(), &_database);
        if (result != SQLITE_OK) {
            //For later throw
        }
    }

    WinRT_EmailDatabaseManager::~WinRT_EmailDatabaseManager()
    {
		sqlite3_close(_database);
	}

    bool WinRT_EmailDatabaseManager::initializeDatabase()
    {
        //Initialize the database with given table array
        for (int i = 0; i < sizeof(TABLE_NAMES) / sizeof(TABLE_NAMES[0]); i++) {
            hstring query = L"CREATE TABLE IF NOT EXISTS " + TABLE_NAMES[i] + L" (id INTEGER PRIMARY KEY AUTOINCREMENT, sender TEXT NOT NULL, recipient TEXT NOT NULL, subject TEXT NOT NULL, content TEXT NOT NULL, timestamp TEXT NOT NULL, type TEXT NOT NULL);";
            if (!_executeQuery(query)) {
                return false;
            }
        }
        return true;
    }

    bool WinRT_EmailDatabaseManager::addEmailTo(const EmailUI::Email& email, const hstring& tableName)
    {
		hstring query = L"INSERT INTO " + tableName + L" (sender, recipient, subject, content, timestamp, type) VALUES ('" + email.getSender() + L"', '" + email.getRecipient() + L"', '" + email.getSubject() + L"', '" + email.getContent() + L"', '" + email.getTimestamp() + L"', '" + email.getType() + L"');";
		return _executeQuery(query);
	}

    IObservableVector<EmailUI::Email> WinRT_EmailDatabaseManager::getEmailsFrom(const hstring& tableName)
    {
		IObservableVector<EmailUI::Email> emails = single_threaded_observable_vector<EmailUI::Email>();
		hstring query = L"SELECT * FROM " + tableName + L";";
		sqlite3_stmt* statement;
		int result = sqlite3_prepare_v2(_database, to_string(query).c_str(), -1, &statement, nullptr);
        if (result != SQLITE_OK) {
            //Later throw
		}
        else {
            while (sqlite3_step(statement) == SQLITE_ROW) {
				int id = sqlite3_column_int(statement, 0);
				hstring sender = to_hstring((const char*)sqlite3_column_text(statement, 1));
                hstring recipient = to_hstring((const char*)sqlite3_column_text(statement, 2));
                hstring subject = to_hstring((const char*)sqlite3_column_text(statement, 3));
                hstring content = to_hstring((const char*)sqlite3_column_text(statement, 4));
                hstring timestamp = to_hstring((const char*)sqlite3_column_text(statement, 5));
                hstring type = to_hstring((const char*)sqlite3_column_text(statement, 6));
                EmailUI::Email email{
					id,
					sender,
					recipient,
					subject,
					content,
					timestamp,
					type
				};
				emails.Append(email);
			}
		}
		sqlite3_finalize(statement);
		return emails;
	}

    void WinRT_EmailDatabaseManager::removeAllEmailsIn(const hstring& tableName)
    {
		hstring query = L"DELETE FROM " + tableName + L";";
		_executeQuery(query);
	}

    bool WinRT_EmailDatabaseManager::moveEmailBetween(const EmailUI::Email& email, const hstring& fromTableName, const hstring& toTableName)
    {
        hstring query = L"INSERT INTO " + toTableName + L" (sender, recipient, subject, content, timestamp, type) VALUES ('" + email.getSender() + L"', '" + email.getRecipient() + L"', '" + email.getSubject() + L"', '" + email.getContent() + L"', '" + email.getTimestamp() + L"', '" + email.getType() + L"";
    	//Delete the email from the original table
        query = query + L"DELETE FROM " + fromTableName + L" WHERE id = " + to_hstring(email.getId()) + L";";
        
        return _executeQuery(query);
    }
    bool WinRT_EmailDatabaseManager::moveAllToTrash(const hstring& fromTableName)
    {
        hstring query = L"INSERT INTO trash (sender, recipient, subject, content, timestamp, type) SELECT sender, recipient, subject, content, timestamp, type FROM " + fromTableName + L";";
		//Delete the email from the original table
		query = query + L"DELETE FROM " + fromTableName + L";";

		return _executeQuery(query);
    }
}
