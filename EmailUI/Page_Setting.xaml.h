#pragma once

#include "Page_Setting.g.h"

namespace winrt::EmailUI::implementation
{
    struct Page_Setting : Page_SettingT<Page_Setting>
    {
        Page_Setting()
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
    struct Page_Setting : Page_SettingT<Page_Setting, implementation::Page_Setting>
    {
    };
}
