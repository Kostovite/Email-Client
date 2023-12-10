#pragma once

#include "Page_Compose.g.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>
#include <winrt/Windows.UI.Text.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::UI::Text;

using Windows::Foundation::IInspectable;
using Microsoft::UI::Xaml::RoutedEventArgs;
using Windows::UI::Xaml::Navigation::NavigationEventArgs;

namespace winrt::EmailUI::implementation
{
    struct Page_Compose : Page_ComposeT<Page_Compose>
    {
    public:
        Page_Compose() {

        }

        EmailUI::Email composeEmail();

        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void OnSendClick(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Page_Compose : Page_ComposeT<Page_Compose, implementation::Page_Compose>
    {
    };
}
