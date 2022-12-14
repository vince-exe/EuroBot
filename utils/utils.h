#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <string>
#include <vector>
#include <fstream>

#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

#include "./JsonReader/json_reader.h"

namespace JsonObjs {
    static JsonReader configs; 
}

namespace Utils {
    void setKeyBoard(TgBot::InlineKeyboardMarkup::Ptr keyboard, const std::vector<std::pair<std::string, std::string>> vec);
}

#endif
