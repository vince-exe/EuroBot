#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <tgbot/tgbot.h>


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
}

class JoinedUsers {
    private:
        static std::vector<int64_t> idVec;

    public: 
        static void insert(int64_t id);

        static bool isIn(int64_t id);
};

#endif
