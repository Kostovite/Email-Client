#include "pch.h"
#include "Page_User_Account_Mail.xaml.h"
#if __has_include("Page_User_Account_Mail.g.cpp")
#include "Page_User_Account_Mail.g.cpp"
#endif

#include "../BackgroundProcessing/sqlite/sqlite3.h"
#include "WinRT_EmailDatabaseManager.h" 

#include <winrt/Windows.Storage.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using Windows::Foundation::Collections::IObservableVector;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    Page_User_Account_Mail::Page_User_Account_Mail()
    {
        InitializeComponent();
        //Get the emails from the database
        _emails = single_threaded_observable_vector<EmailUI::Email>();

        EmailUI::Email sampleEmail{
            1,
            /* sender */ L"john.doe@example.com",
            /* recipient */ L"jane.smith@example.com",
            /* subject */ L"Sample Subject",
            /* content */ L"Sample Content",
            /* timestamp */ L"2023-11-27 10:30:00",
            /* type */ L"inbox"
        };
        _emails.Append(sampleEmail);

        EmailUI::WinRT_EmailDatabaseManager emailDatabaseManager;
        emailDatabaseManager.initializeDatabase();
        
        //Get the emails from the database
        IObservableVector<EmailUI::Email> inboxEmails = emailDatabaseManager.getEmailsFrom(L"inbox");

        for (EmailUI::Email email : inboxEmails) {
			_emails.Append(email);
		}
        
    }

    Windows::Foundation::Collections::IObservableVector<EmailUI::Email> Page_User_Account_Mail::Emails()
    {
        return _emails;
    }
}
