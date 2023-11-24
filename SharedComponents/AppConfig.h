#pragma once

#include <string>
#include <unordered_map>

class AppConfig {
private:
    std::unordered_map<std::string, std::string> _settings;
    std::string _sanitizeKey(const std::string& key);
public:
    AppConfig();
    ~AppConfig();
public:
    bool loadConfigFromFile(const std::string& filePath);
    bool saveConfigToFile(const std::string& filePath);
    std::string getServerAddress() const;
    void setServerAddress(const std::string& serverAddress);
};
