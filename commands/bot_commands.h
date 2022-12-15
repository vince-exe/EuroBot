#ifndef BOT_COMMANDS_H
#define BOT_COMMANDS_H

#include <tgbot/tgbot.h>
#include <iostream>

#include "../utils/utils.h"

class BotCommands {
private:
    TgBot::Bot* bot;

    TgBot::EventBroadcaster* eventBroadCaster;

    TgBot::InlineKeyboardMarkup::Ptr playKeyBoard;

    TgBot::InlineKeyboardMarkup::Ptr backBoardCopyrights;

private:
    void start();
    
    void play();

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

    TgBot::InlineKeyboardMarkup::Ptr getPlayKeyBoard();

    TgBot::InlineKeyboardMarkup::Ptr getBackCopyRightsBoard();
};

#endif
