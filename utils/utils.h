#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <tgbot/tgbot.h>
#include <random>

#include "../database/database.h"
#include "./AdminSettings/admin_settings.h"

namespace BotUtils {
    /**
     * @brief Set the TgBot::InlineKeyboardMarkup::Ptr object
     * 
     * @param keyboard the keyboard to set
     * @param vec a vector that contains all the buttons
    */
    void setKeyBoard(TgBot::InlineKeyboardMarkup::Ptr keyboard, const std::vector<std::pair<std::string, std::string>> vec);

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

    /**
     * @brief generate a random number between ( min; max )
     * 
     * @param min min generation value
     * @param max max generation value
     * 
     * @return a random value between ( min; max )
     */
    int getRandom(int min, int max);

    /**
     * @brief print the database fatal error message in the terminal
     * 
     * @param sqlErr the DBErros::SqlErros* pointer to struct for database errors
     */
    void printFatalErrorDB(DBErrors::SqlErrors* sqlErr);

    /**
     * @brief return the current date under a specific format
     * 
     * @param format the format to build the date
     * 
     * @return the current date under a specific given format
     */
    const std::string currentDateTime(const std::string& format);
    
    /**
     * @brief return a profit pair
     * 
     * @param bets vector of bets
     */
    std::pair<std::string, int> getProfit(std::vector<Bet>& bets); 
}

#endif
