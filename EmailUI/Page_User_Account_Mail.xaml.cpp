#include "pch.h"
#include "Page_User_Account_Mail.xaml.h"
#if __has_include("Page_User_Account_Mail.g.cpp")
#include "Page_User_Account_Mail.g.cpp"
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    Page_User_Account_Mail::Page_User_Account_Mail(/*hstring tableName*/)
    {
        InitializeComponent();
    }

    Windows::Foundation::Collections::IObservableVector<EmailUI::Email> Page_User_Account_Mail::Emails()
    {
        return _emails;
    }

    void Page_User_Account_Mail::OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        //Get the box_value from the navigation parameter
        auto tableName = unbox_value<hstring>(e.Parameter());

        EmailUI::WinRT_EmailDatabaseManager emailDatabaseManager;
        emailDatabaseManager.initializeDatabase();

        //Check if the tableName is inbox
        if (tableName == L"inbox") {
            //Using POP3 to push emails from the server to the database
            POP3_Client pop3Client("192.168.1.174", 1100, USER, PASSWORD);
            std::string sender, recipient, subject, content;
            auto [success, message] = pop3Client.receiveEmail(sender, recipient, subject, content);

            if (success)
            {
                Convert::Convertor convert;
                subject = convert.mimeToRtf(subject);
                EmailUI::Email newEmail(0, winrt::to_hstring(sender), winrt::to_hstring(recipient), L"Test", winrt::to_hstring(subject), winrt::to_hstring(content), L"Test", L"");
                emailDatabaseManager.addEmailTo(newEmail, L"inbox");
            }
		}

        //Get the emails from the database
        _emails = single_threaded_observable_vector<EmailUI::Email>();

        //Get the emails from the database
        IObservableVector<EmailUI::Email> inboxEmails = emailDatabaseManager.getEmailsFrom(tableName);

        for (EmailUI::Email email : inboxEmails) {
            _emails.Append(email);
        }
    }

    void Page_User_Account_Mail::emailItemClick(IInspectable const&, ItemClickEventArgs const&)
    {
        table().ItemClick([this](auto&& sender, auto&& args)
            {
                if (EmailUI::Email clickedItem = args.ClickedItem().try_as<EmailUI::Email>())
                {
                    //Update the content TextBlock in the VIEW PANE with details from the clicked Email
                    Subject().Text(clickedItem.getSubject());

                    Sender().Text(L"From: " + clickedItem.getSender());

                    hstring recipient = L"To: " + clickedItem.getRecipient();
                    recipient = recipient + clickedItem.getBcc();
                    Recipient().Text(recipient);
                    
                    Timestamp().Text(clickedItem.getTimestamp());

                    Body().Document().SetText(static_cast<Microsoft::UI::Text::TextSetOptions>(Microsoft::UI::Text::TextSetOptions::FormatRtf), clickedItem.getContent());
                }
            });
    }
}
