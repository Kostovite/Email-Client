#pragma once

#include "Attachment.g.h"
#include "../Components/cppcodec/base64_default_rfc4648.hpp"

namespace winrt::EmailUI::implementation
{
    struct Attachment : AttachmentT<Attachment>
    {
    private:
        hstring _fileName;
        hstring _fileType;
        hstring _base64Data;
    public:
        Attachment() = default;

        hstring FileName();
        hstring FileType();
        hstring Base64Data();
        void FileName(hstring const& value);
        void FileType(hstring const& value);
        void Base64Data(hstring const& value);
    };
}

namespace winrt::EmailUI::factory_implementation
{
    struct Attachment : AttachmentT<Attachment, implementation::Attachment>
    {
    };
}
