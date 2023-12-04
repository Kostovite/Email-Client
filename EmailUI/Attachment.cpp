#include "pch.h"
#include "Attachment.h"
#if __has_include("Attachment.g.cpp")
#include "Attachment.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{
    hstring Attachment::FileName()
    {
        return _fileName;
    }

	hstring Attachment::FileType()
	{
		return _fileType;
	}

    hstring Attachment::Base64Data()
	{
		return _base64Data;
	}

	void Attachment::FileName(hstring const& value)
	{
		_fileName = value;
	}

	void Attachment::FileType(hstring const& value)
	{
		_fileType = value;
	}

	void Attachment::Base64Data(hstring const& value)
	{
		_base64Data = value;
	}
	
}
