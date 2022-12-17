#ifndef BOT_COMMANDS_H
#define BOT_COMMANDS_H

#include <tgbot/tgbot.h>
#include <iostream>

#include "../utils/utils.h"

class BotCommands {
private:
    TgBot::Bot* bot;

    TgBot::EventBroadcaster* eventBroadCaster;

    TgBot::InlineKeyboardMarkup::Ptr startKeyBoard;

    TgBot::InlineKeyboardMarkup::Ptr backBoardCopyrights;

    TgBot::InlineKeyboardMarkup::Ptr settingsBoard;
    
    TgBot::InlineKeyboardMarkup::Ptr backRules;
    
private:
    void start();

    void settings();

    void callBackQuery();

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

    /**
     * @brief Get the startKeyBoard property
     * 
     * @return TgBot::InlineKeyboardMarkup::Ptr* 
    */
};

#endif
