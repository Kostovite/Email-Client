#pragma once

#include <string>
#include <unordered_map>

using std::string;

class AppConfig {
private:
    std::unordered_map<string, string> _settings;
    string _sanitizeKey(const string& key);
public:
    AppConfig();
    ~AppConfig();
public:
    bool loadConfigFromFile(const string& filePath);
    bool saveConfigToFile(const string& filePath);
    string getServerAddress() const;
    void setServerAddress(const string& serverAddress);
};
