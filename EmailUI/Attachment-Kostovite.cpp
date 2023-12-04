#include "pch.h"
#include "Attachment.h"
#if __has_include("Attachment.g.cpp")
#include "Attachment.g.cpp"
#endif

#include "../BackgroundProcessing/cppcodec/base64_default_rfc4648.hpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    Attachment::Attachment()
    {
    }

    int32_t Attachment::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Attachment::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
