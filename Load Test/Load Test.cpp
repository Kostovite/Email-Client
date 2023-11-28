
#include <iostream>
#include "../BackgroundProcessing/EmailDatabaseManager.h"

int main()
{
    EmailDatabaseManager emailDatabaseManager;
    auto emails = emailDatabaseManager.getEmailsFrom("inbox");
    for (auto email : emails)
    {
        std::cout << email.getId() << std::endl;
        std::cout << email.getSubject() << std::endl;
        std::cout << email.getSender() << std::endl;
        std::cout << email.getContent() << std::endl;
        std::cout << email.getTimestamp() << std::endl;
        std::cout << email.getType() << std::endl;
    }
}