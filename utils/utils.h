#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <string>
#include <vector>

#include <tgbot/tgbot.h>

namespace Utils {
    
    void setKeyBoard(TgBot::InlineKeyboardMarkup::Ptr& keyboard, const std::vector<std::pair<std::string, std::string>> vec);
}

#endif
