#include <iostream>
#include <string>

#include "rtf_Mime.h"

int main() {
    std::string rtfContent = "{\\rtf1\\ansi\\b Hello \\b0 World}";

    std::string mimeContent = rtfToMime(rtfContent);
    std::cout << mimeContent << std::endl;

    std::string decoded = mimeToRtf(mimeContent);
    std::cout << decoded << std::endl;

    return 0;
}
