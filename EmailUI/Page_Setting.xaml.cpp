#include "pch.h"
#include "Page_Setting.xaml.h"
#if __has_include("Page_Setting.g.cpp")
#include "Page_Setting.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    int32_t Page_Setting::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Page_Setting::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Page_Setting::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
