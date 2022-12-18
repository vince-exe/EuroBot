#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <string>
#include <vector>
#include <fstream>

#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

#include "./JsonReader/json_reader.h"

namespace Utils {
    /**
     * @brief Set the TgBot::InlineKeyboardMarkup::Ptr object
     * 
     * @param keyboard the keyboard to set
     * @param vec a vector that contains all the buttons
    */
    void setKeyBoard(TgBot::InlineKeyboardMarkup::Ptr keyboard, const std::vector<std::pair<std::string, std::string>> vec);

    /**
     * @brief Check if the creator has access to the commands
     * 
    */
    static int idCreator = 0;

    /**
     * @brief Return one of the two given emojis based on a condition
     * 
     * @param s a string where the condition should appear
     * 
     * @param condition the condition that the string has to respect
     * 
     * @param emoji the two emoji
     * 
     */
    std::string getEmoji(const std::string s, const std::string condition, const std::pair<std::string, std::string> emoji);
}

#endif
