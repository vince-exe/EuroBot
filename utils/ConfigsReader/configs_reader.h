#ifndef CONFIGS_READER_H
#define CONFIGS_READER_H

#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigsReader {
public:
    static json configs;

public:
    static bool isAuthorizedRole(const std::string role);

    static void readJson(const std::string path);
};

#endif