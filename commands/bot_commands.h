#ifndef BOT_COMMANDS_H
#define BOT_COMMANDS_H

#include <tgbot/tgbot.h>
#include <iostream>

#include "../utils/utils.h"
#include "../utils/JsonReader/json_reader.h"
#include "../utils/AdminSettings/admin_settings.h"


class BotCommands {
private:
    TgBot::Bot* bot;

    TgBot::EventBroadcaster* eventBroadCaster;
        
    TgBot::InlineKeyboardMarkup::Ptr startKeyBoard;

    TgBot::InlineKeyboardMarkup::Ptr backToStartPanel;

    TgBot::InlineKeyboardMarkup::Ptr settingsBoard;

    TgBot::InlineKeyboardMarkup::Ptr generalBoard;

    TgBot::InlineKeyboardMarkup::Ptr backToSettings;
    
private:
    void start();
    
    void update();
    
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
