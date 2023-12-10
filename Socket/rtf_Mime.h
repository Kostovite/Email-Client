#pragma once

#ifdef CONVERTOR_CLIENT_EXPORTS
#define CONVERTOR_CLIENT_API __declspec(dllexport)
#else
#define CONVERTOR_CLIENT_API __declspec(dllimport)
#endif

#include "pch.h"
#include "../Components/cppcodec/base64_default_rfc4648.hpp"

#include <iostream>
#include <string>
#include <sstream>

namespace Convert {
    extern "C" CONVERTOR_CLIENT_API class Convertor {
    public:
        __declspec(dllexport) std::string rtfToMime(const std::string& rtfContent) {
            // Base64 encode the RTF content
            std::string base64Encoded = cppcodec::base64_rfc4648::encode(rtfContent);

            // Create the MIME message
            std::ostringstream mimeStream;
            mimeStream << "Content-Type: text/rtf; charset=\"utf-8\"\r\n";
            mimeStream << "Content-Transfer-Encoding: base64\r\n\r\n";
            mimeStream << base64Encoded;

            return mimeStream.str();
        }

        __declspec(dllexport) std::string mimeToRtf(const std::string& mimeContent) {
            // Find the position of the MIME content
            std::size_t pos = mimeContent.find("\r\n\r\n");
            if (pos == std::string::npos) {
                // Invalid MIME content
                return "";
            }

            // Extract the base64-encoded content
            std::string base64Encoded = mimeContent.substr(pos + 4);

            // Base64 decode the content
            std::string decoded = cppcodec::base64_rfc4648::decode<std::string>(base64Encoded);

            return decoded;
        }
    };
}