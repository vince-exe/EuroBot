#include "configs_reader.h"

json ConfigsReader::configs;

bool ConfigsReader::isAuthorizedRole(const std::string role) {
    for(auto it : ConfigsReader::configs["authorizedRoles"]) {
        if(it == role) { return true; }
    }

    return false;
}

void ConfigsReader::readJson(const std::string path) {
    std::ifstream ifs(path);
    ConfigsReader::configs = json::parse(ifs);
}