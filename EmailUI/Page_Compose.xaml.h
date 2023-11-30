#pragma once

#include "Page_Compose.g.h"

namespace winrt::EmailUI::implementation
{
    struct Page_Compose : Page_ComposeT<Page_Compose>
    {
        Page_Compose()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        EmailUI::Email composeEmail();

        //OnSendClick button
        void OnSendClick(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Page_Compose : Page_ComposeT<Page_Compose, implementation::Page_Compose>
    {
    };
}
