#pragma once

#include "Page_User_Account_Mail.g.h"
#include "Email.h"

using namespace winrt;

namespace winrt::EmailUI::implementation
{
    struct Page_User_Account_Mail : Page_User_Account_MailT<Page_User_Account_Mail>
    {
    private:
        Windows::Foundation::Collections::IObservableVector<EmailUI::Email> _emails{};
    public:
        Page_User_Account_Mail();

        Windows::Foundation::Collections::IObservableVector<EmailUI::Email> Emails();

    public:
        
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Page_User_Account_Mail : Page_User_Account_MailT<Page_User_Account_Mail, implementation::Page_User_Account_Mail>
    {
    };
}
