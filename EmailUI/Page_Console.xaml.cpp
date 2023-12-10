#include "pch.h"
#include "Page_Console.xaml.h"
#if __has_include("Page_Console.g.cpp")
#include "Page_Console.g.cpp"
#endif

#include <winrt/Windows.Storage.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    int32_t Page_Console::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Page_Console::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Page_Console::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
