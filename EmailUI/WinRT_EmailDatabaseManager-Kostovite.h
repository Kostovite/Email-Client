#pragma once

#include "WinRT_EmailDatabaseManager.g.h"

#include "../BackgroundProcessing/sqlite/sqlite3.h"

namespace winrt::EmailUI::implementation
{
    struct WinRT_EmailDatabaseManager : WinRT_EmailDatabaseManagerT<WinRT_EmailDatabaseManager>
    {
    private:
        sqlite3* _database;
        hstring _databasePath;
        bool _executeQuery(const hstring& query);
    public:
        WinRT_EmailDatabaseManager();
        ~WinRT_EmailDatabaseManager();

        const hstring TABLE_NAMES[4] = { L"inbox", L"sent", L"drafts", L"trash" };

        bool initializeDatabase();

        bool addEmailTo(const EmailUI::Email& email, const hstring& tableName);
        Windows::Foundation::Collections::IObservableVector<EmailUI::Email> getEmailsFrom(const hstring& tableName);
        void removeAllEmailsIn(const hstring& tableName);
        bool moveEmailBetween(const EmailUI::Email& email, const hstring& fromTableName, const hstring& toTableName);
        bool moveAllToTrash(const hstring& fromTableName);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct WinRT_EmailDatabaseManager : WinRT_EmailDatabaseManagerT<WinRT_EmailDatabaseManager, implementation::WinRT_EmailDatabaseManager>
    {
    };
}
