#ifndef COMMANDS_UTILS_H
#define COMMANDS_UTILS_H

#include <tgbot/tgbot.h>
#include <string>
#include <nlohmann/json.hpp>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <utility>

#include "../JsonReader/json_reader.h"
#include "../AdminSettings/admin_settings.h"
#include "../utils.h"

class CommandsUtils {
public:
    static int maxCoinLen;

    static int idCreator;

    static bool updateCommandAuth;

    static bool startCommandAuth;
    
    static bool gameStarted;
    
    static bool startCommand;

    static bool settingsButtonClicked;
    
    static std::string lastCommand;
    
public:
    static bool isValidGroup(int64_t id);

    static bool startBot(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user);

    static void printAdminJoin(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user);

    static void printConfirmBoxReset(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    static void printGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard, bool isPrivate);

    static void printInvalidArguments(TgBot::Bot* bot, TgBot::Message::Ptr message);
    
    static void editGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard);
    
    static void printSettingsPanel(TgBot::Bot* bot, std::pair<int64_t, int32_t> ids, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    static void editSettingsPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);
    
    static void printToS(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    static void printCopyRights(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    static void printStartPanel(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard);

    static void printStartPrivatePanel(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user);

    static int countArguments(const std::string command, const std::string message);
    
    static std::vector<std::string> getArguments(const std::string command, const std::string message);

    static bool isValid(const std::string command, const std::string message);
};

#endif
