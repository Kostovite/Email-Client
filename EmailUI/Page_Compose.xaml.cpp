#include "pch.h"
#include "Page_Compose.xaml.h"
#if __has_include("Page_Compose.g.cpp")
#include "Page_Compose.g.cpp"
#endif

#include <ctime>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

//Define a sample sender
hstring sender = L"nguyenvana@gmail.com";

namespace winrt::EmailUI::implementation
{
	EmailUI::Email Page_Compose::composeEmail()
	{
		hstring cc = ccTextBox().Text();
		hstring bcc = bccTextBox().Text();
		hstring subject = subjectTextBox().Text();
		hstring body = bodyTextBox().Text();
		//Timestamp format: dd/mm/yyyy hh:mm:ss
		time_t now = time(0);
		tm* ltm = new tm;
		localtime_s(ltm, &now);
		hstring timestamp = to_hstring(ltm->tm_mday) + L"/" + to_hstring(ltm->tm_mon + 1) + L"/" + to_hstring(ltm->tm_year + 1900) + L" " + to_hstring(ltm->tm_hour) + L":" + to_hstring(ltm->tm_min) + L":" + to_hstring(ltm->tm_sec);
		hstring type = L"sent";

		EmailUI::Email composed(0, sender, cc, bcc, subject, body, timestamp, type);

		return composed;
	}

	void Page_Compose::OnSendClick(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
	{
		sendButton().Content(box_value(L"Sended"));
		EmailUI::WinRT_EmailDatabaseManager emailDatabase;
		emailDatabase.addEmailTo(composeEmail(), L"sent");
	}
}
