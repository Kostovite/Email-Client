#pragma once

#include "Page_User_Account_Mail.g.h"
#include "Email.h"

#include <winrt/Windows.UI.Xaml.Navigation.h>

using namespace winrt;
using winrt::Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs;

namespace winrt::EmailUI::implementation
{
    struct Page_User_Account_Mail : Page_User_Account_MailT<Page_User_Account_Mail>
    {
    private:
        Windows::Foundation::Collections::IObservableVector<EmailUI::Email> _emails{};
    public:
        Page_User_Account_Mail();

        Windows::Foundation::Collections::IObservableVector<EmailUI::Email> Emails();

        void OnNavigatedTo(winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const&);
        void emailItemClick(IInspectable const&, ItemClickEventArgs const&);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Page_User_Account_Mail : Page_User_Account_MailT<Page_User_Account_Mail, implementation::Page_User_Account_Mail>
    {
    };
}
