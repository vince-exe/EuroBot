#ifndef BOT_COMMANDS_H
#define BOT_COMMANDS_H

#include <tgbot/tgbot.h>
#include <unordered_map>
#include <iostream>

#include "../utils/utils.h"
#include "../database/database.h"
#include "../utils/CommandsUtils/commands_utils.h"
#include "../utils/JsonReader/json_reader.h"
#include "../utils/AdminSettings/admin_settings.h"

#include "../user/user.h"
#include "../loan/loan.h"

class BotCommands {
private:
    TgBot::Bot* bot;

    TgBot::EventBroadcaster* eventBroadCaster;
        
    TgBot::InlineKeyboardMarkup::Ptr startKeyBoard;

    TgBot::InlineKeyboardMarkup::Ptr backToStartPanel;

    TgBot::InlineKeyboardMarkup::Ptr settingsBoard;

    TgBot::InlineKeyboardMarkup::Ptr generalBoard;

    TgBot::InlineKeyboardMarkup::Ptr backToSettings;

    TgBot::InlineKeyboardMarkup::Ptr confirmBoard;

    TgBot::CallbackQuery::Ptr query;

public:
    DBErrors::SqlErrors sqlErrs;

private:
    void start();
    
    void update();
    
    void join();
    
    void infoGame();
    
    void stake();

    void give_to();

    void callBackQuery();

    void stats();
    
public:
    /**
     * @brief Construct a new Bot Commands object
     * 
     * @param bot a pointer to an existing TgBot::Bot istance
     * 
     */
    BotCommands(TgBot::Bot* bot);

    ~BotCommands();

    /**
     * @brief Initialize the class commands
     * 
     */
    void init();
};

#endif
