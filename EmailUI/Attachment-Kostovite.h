#pragma once

#include "Attachment.g.h"

namespace winrt::EmailUI::implementation
{
    struct Attachment : AttachmentT<Attachment>
    {
        Attachment();

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Attachment : AttachmentT<Attachment, implementation::Attachment>
    {
    };
}
