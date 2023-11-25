#include "AppConfig.h"

#include <fstream>

using std::ifstream;

string AppConfig::_sanitizeKey(const string& key)
{
    return key;
}

AppConfig::AppConfig()
{
}

AppConfig::~AppConfig()
{
}

bool AppConfig::loadConfigFromFile(const string& filePath) {
    std::ifstream configFile(filePath);
    if (!configFile.is_open()) {
        return false;  // Unable to open the file
    }
    string line;
    while (std::getline(configFile, line)) {
        size_t delimiterPos = line.find('=');
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);
            _settings[_sanitizeKey(key)] = value;
        }
    }
    configFile.close();
    return true;
}

bool AppConfig::saveConfigToFile(const string& filePath) {
	std::ofstream configFile(filePath);
    if (!configFile.is_open()) {
		return false;  // Unable to open the file
	}
    for (auto& setting : _settings) {
		configFile << setting.first << "=" << setting.second << std::endl;
	}
	configFile.close();
	return true;
}

string AppConfig::getServerAddress() const {
	return _settings.at("server_address");
}

void AppConfig::setServerAddress(const string& serverAddress) {
	_settings["server_address"] = serverAddress;
}