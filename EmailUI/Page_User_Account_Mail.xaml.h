#pragma once

#include "Page_User_Account_Mail.g.h"
#include "Email.h"
#include "WinRT_EmailDatabaseManager.h"
#include "POP3_Client.h"
#include "rtf_Mime.h"

#include <winrt/Windows.UI.Xaml.Navigation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.UI.Xaml.Documents.h>
#include <winrt/Microsoft.UI.Text.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

using namespace winrt;
using winrt::Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs;
using namespace Microsoft::UI::Xaml;
using namespace Windows::UI::Xaml::Documents;
using Windows::Foundation::Collections::IObservableVector;

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
