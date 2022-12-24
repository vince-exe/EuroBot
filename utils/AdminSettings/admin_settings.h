#ifndef ADMIN_SETTINGS_H
#define ADMIN_SETTINGS_H

#include <unordered_map>
#include <string>

class AdminSettings {
private:
    static std::unordered_map<std::string, std::string> settingsList;

public:
    static void init();

    static int size();

    static void clear();
    
    static bool setKeyValue(std::string key, std::string value);

    static std::string getValueByKey(const std::string key);
    
    static double getMoney();

    static int dailyBets();

    static bool giveMoney();

    static bool showClassification();

    static int getWinPercentage();

    static int getLosePercentage();

    static std::string getCoinName();

    static bool exist(const std::string key);
};

#endif
