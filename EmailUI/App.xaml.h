#pragma once

#include "App.xaml.g.h"
#include "Email.h"
#include "WinRT_EmailDatabaseManager.h"
#include "Attachment.h"

namespace winrt::EmailUI::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}
