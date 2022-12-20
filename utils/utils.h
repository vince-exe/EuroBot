#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

#include "./JsonReader/json_reader.h"
#include "./AdminSettings/admin_settings.h"

namespace CommandsUtils {
    static int maxCoinLen = 10;
    
    void printGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard, bool isPrivate);

    void printInvalidArguments(TgBot::Bot* bot, TgBot::Message::Ptr message);
    
    void editGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard);
    
    void printSettingsPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    void editSettingsPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);
    
    void printToS(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    void printCopyRights(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    void printStartPanel(TgBot::Bot* bot, TgBot::Message::Ptr message, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    void printStartPrivatePanel(TgBot::Bot* bot, TgBot::Message::Ptr message, TgBot::ChatMember::Ptr user);

    int countArguments(const std::string command, const std::string message);
    
    std::vector<std::string> getArguments(const std::string command, const std::string message);

    bool isValid(const std::string command, const std::string message);
}


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

    static bool updateCommandAuth = false;
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
