#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "Page_User_Account_Mail.xaml.h"

#include <winrt/Windows.UI.Xaml.Interop.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;;
using winrt::Microsoft::UI::Xaml::Controls::NavigationView, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::NavigationView_ItemInvoked(NavigationView const& sender, NavigationViewItemInvokedEventArgs const& args)
    {
        //if (args.IsSettingsInvoked())
        //{
        //    //ContentFrame().Navigate(xaml_typename<Email::Page_Settings>(), nullptr);
        //}

        if (args.InvokedItemContainer().Tag().as<winrt::hstring>() == L"Email.Page_User_Account_Inbox")
        {
            auto currentPagetype = ContentFrame().CurrentSourcePageType();
            auto mailPage = xaml_typename<EmailUI::Page_User_Account_Mail>();
            if (currentPagetype != mailPage)
            {
				ContentFrame().Navigate(mailPage, nullptr);
			}
        }

        if (args.InvokedItemContainer().Tag().as<winrt::hstring>() == L"Email.Page_User_Account_Sent")
        {
			auto currentPagetype = ContentFrame().CurrentSourcePageType();
			auto mailPage = xaml_typename<EmailUI::Page_User_Account_Mail>();
            if (currentPagetype != mailPage)
            {
                ContentFrame().Navigate(mailPage, nullptr);
            }
        }

        if (args.InvokedItemContainer().Tag().as<winrt::hstring>() == L"Email.Page_User_Account_Drafts")
        {
            auto currentPagetype = ContentFrame().CurrentSourcePageType();
            auto mailPage = xaml_typename<EmailUI::Page_User_Account_Mail>();
            if (currentPagetype != mailPage)
            {
                ContentFrame().Navigate(mailPage, nullptr);
            }
        }

        if (args.InvokedItemContainer().Tag().as<winrt::hstring>() == L"Email.Page_User_Account_Trash")
        {
			auto currentPagetype = ContentFrame().CurrentSourcePageType();
			auto mailPage = xaml_typename<EmailUI::Page_User_Account_Mail>();
            if (currentPagetype != mailPage)
            {
				ContentFrame().Navigate(mailPage, nullptr);
			}
		}
    }
}
