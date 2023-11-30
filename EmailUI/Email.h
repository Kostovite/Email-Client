#pragma once

#include "Email.g.h"

namespace winrt::EmailUI::implementation
{
    struct Email : EmailT<Email>
    {
    private:
        int32_t _id{};
        hstring _sender;
        hstring _recipient;
        hstring _bcc;
        hstring _subject;
        hstring _content;
        hstring _timestamp;
        hstring _type;

        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> _propertyChanged;

    public:
        Email() = default;
        Email(int32_t id, hstring sender, hstring recipient, hstring bcc, hstring subject, hstring content, hstring timestamp, hstring type);

        event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(event_token const& token) noexcept;

    public:
        int32_t getId();
		hstring getSender();
        hstring getRecipient();
        hstring getBcc();
        hstring getSubject();
        hstring getContent();
        hstring getTimestamp();
        hstring getType();

        void setId(int32_t value);
        void setSender(hstring value);
        void setRecipient(hstring value);
        void setBcc(hstring value);
		void setSubject(hstring value);
        void setContent(hstring value);
		void setTimestamp(hstring value);
        void setType(hstring value);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Email : EmailT<Email, implementation::Email>
    {
    };
}
