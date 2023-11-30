#pragma once

#include "MainWindow.g.h"

using winrt::Microsoft::UI::Xaml::Controls::NavigationView, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs;

namespace winrt::EmailUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void MainWindow::NavigationView_ItemInvoked(NavigationView const& sender, NavigationViewItemInvokedEventArgs const& args);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
