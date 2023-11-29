#pragma once

#include "Page_Console.g.h"

namespace winrt::EmailUI::implementation
{
    struct Page_Console : Page_ConsoleT<Page_Console>
    {
        Page_Console()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Page_Console : Page_ConsoleT<Page_Console, implementation::Page_Console>
    {
    };
}
