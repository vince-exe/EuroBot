#include "admin_settings.h"

std::unordered_map<std::string, std::string> AdminSettings::settingsList;

void AdminSettings::init() {
    AdminSettings::settingsList.insert({"startsMoney", "1000"});

    AdminSettings::settingsList.insert({"dailyBets", "-1"});

    AdminSettings::settingsList.insert({"giveMoney", "true"});

    AdminSettings::settingsList.insert({"showClassification", "true"});

    AdminSettings::settingsList.insert({"winPercentage", "50"});

    AdminSettings::settingsList.insert({"losePercentage", "100"});

    AdminSettings::settingsList.insert({"coinName", "coins"});
}

void AdminSettings::setKeyValue(std::string key, std::string value) {
    AdminSettings::settingsList.insert({key, value});
}

std::string AdminSettings::getValueByKey(const std::string key) {
    return AdminSettings::settingsList[key];
}

double AdminSettings::getMoney() {
    return std::stod(AdminSettings::settingsList["startsMoney"]);
}

int AdminSettings::dailyBets() {
    return std::atoi(AdminSettings::settingsList["dailyBets"].c_str());
}

bool AdminSettings::giveMoney() {
    return (AdminSettings::settingsList["giveMoney"] == "true") ? true : false;
}

bool AdminSettings::showClassification() {
    return (AdminSettings::settingsList["showClassification"] == "true") ? true : false;
}

int AdminSettings::getWinPercentage() {
    return std::atoi(AdminSettings::settingsList["winPercentage"].c_str());
}

int AdminSettings::getLosePercentage() {
    return std::atoi(AdminSettings::settingsList["losePercentage"].c_str());
}

std::string AdminSettings::getCoinName() {
    return AdminSettings::settingsList["coinName"];
}