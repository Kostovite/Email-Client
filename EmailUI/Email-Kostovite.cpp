#include "pch.h"
#include "Email.h"
#if __has_include("Email.g.cpp")
#include "Email.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::EmailUI::implementation
{

    Email::Email(int32_t id, hstring sender, hstring recipient, hstring bcc, hstring subject, hstring content, hstring timestamp, hstring type)
    {
        this->_id = id;
		this->_sender = sender;
		this->_recipient = recipient;
		this->_bcc = bcc;
		this->_subject = subject;
		this->_content = content;
		this->_timestamp = timestamp;
		this->_type = type;
    }

	event_token Email::PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return _propertyChanged.add(handler);
	}

	void Email::PropertyChanged(event_token const& token) noexcept
	{
		_propertyChanged.remove(token);
	}

    int32_t Email::getId()
	{
		return this->_id;
	}

hstring Email::getSender()
	{
		return this->_sender;
	}

	hstring Email::getRecipient()
	{
		return this->_recipient;
	}

	hstring Email::getBcc()
	{
		return this->_bcc;
	}

	hstring Email::getSubject()
	{
		return this->_subject;
	}

	hstring Email::getContent()
	{
		return this->_content;
	}

	hstring Email::getTimestamp()
	{
		return this->_timestamp;
	}

	hstring Email::getType()
	{
		return this->_type;
	}

	void Email::setId(int32_t id)
	{
		if (this->_id != id)
		{
			this->_id = id;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"id" });
		}
	}

	void Email::setSender(hstring sender)
	{
		if (this->_sender != sender)
		{
			this->_sender = sender;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"sender" });
		}
	}

	void Email::setRecipient(hstring recipient)
	{
		if (this->_recipient != recipient)
		{
			this->_recipient = recipient;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"recipient" });
		}
	}

	void Email::setBcc(hstring bcc)
	{
		if (this->_bcc != bcc)
		{
			this->_bcc = bcc;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"bcc" });
		}
	}

	void Email::setSubject(hstring subject)
	{
		if (this->_subject != subject)
		{
			this->_subject = subject;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"subject" });
		}
	}

	void Email::setContent(hstring content)
	{
		if (this->_content != content)
		{
			this->_content = content;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"content" });
		}
	}

	void Email::setTimestamp(hstring timestamp)
	{
		if (this->_timestamp != timestamp)
		{
			this->_timestamp = timestamp;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"timestamp" });
		}
	}

	void Email::setType(hstring type)
	{
		if (this->_type != type)
		{
			this->_type = type;
			_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"type" });
		}
	}
}
