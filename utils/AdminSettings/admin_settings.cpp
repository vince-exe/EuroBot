#include "admin_settings.h"

std::unordered_map<std::string, std::string> AdminSettings::settingsList;

void AdminSettings::init() {
    AdminSettings::settingsList.insert({"SoldiIniziali", "1000"});

    AdminSettings::settingsList.insert({"ScommesseGiornaliere", "-1"});

    AdminSettings::settingsList.insert({"RegaloSoldi", "true"});

    AdminSettings::settingsList.insert({"MostraClassifica", "true"});

    AdminSettings::settingsList.insert({"PercentualeVittoria", "50"});

    AdminSettings::settingsList.insert({"PercentualeSconfitta", "100"});

    AdminSettings::settingsList.insert({"NomeValuta", "coins"});
}

int AdminSettings::size() {
    return AdminSettings::settingsList.size();
}    

void AdminSettings::clear() {
    AdminSettings::settingsList.clear();
}

bool AdminSettings::setKeyValue(std::string key, std::string value) {
    auto it = AdminSettings::settingsList.find(key);
    if(it == AdminSettings::settingsList.end()) { return false; }

    it->second = value;
    return true;
}

std::string AdminSettings::getValueByKey(const std::string key) {
    return AdminSettings::settingsList[key];
}

int AdminSettings::getMoney() {
    return std::atoi(AdminSettings::settingsList["SoldiIniziali"].c_str());
}

int AdminSettings::dailyBets() {
    return std::atoi(AdminSettings::settingsList["ScommesseGiornaliere"].c_str());
}

bool AdminSettings::giveMoney() {
    return (AdminSettings::settingsList["RegaloSoldi"] == "true") ? true : false;
}

bool AdminSettings::showClassification() {
    return (AdminSettings::settingsList["MostraClassifica"] == "true") ? true : false;
}

int AdminSettings::getWinPercentage() {
    return std::atoi(AdminSettings::settingsList["PercentualeVittoria"].c_str());
}

int AdminSettings::getLosePercentage() {
    return std::atoi(AdminSettings::settingsList["PercentualeSconfitta"].c_str());
}

std::string AdminSettings::getCoinName() {
    return AdminSettings::settingsList["NomeValuta"];
}

bool AdminSettings::exist(const std::string key) {
    return (AdminSettings::settingsList.find(key) != AdminSettings::settingsList.end());
}