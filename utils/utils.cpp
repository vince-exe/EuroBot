#include "utils.h"


void BotUtils::setKeyBoard(TgBot::InlineKeyboardMarkup::Ptr keyboard, const std::vector<std::pair<std::string, std::string>> vec) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;

    for(auto it : vec) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);

        button->text = it.first;
        button->callbackData = it.second;

        row.push_back(button);
    }

    keyboard->inlineKeyboard.push_back(row);
}

std::string BotUtils::getEmoji(const std::string s, const std::string condition, const std::pair<std::string, std::string> emoji) {
    return (s == condition ) ? emoji.first : emoji.second;
}

std::vector<int64_t> JoinedUsers::idVec;

void JoinedUsers::insert(int64_t id) {
    JoinedUsers::idVec.push_back(id);
}

bool JoinedUsers::isIn(int64_t id) {
    for(auto& id_ : JoinedUsers::idVec) {
        if(id_ == id) { return true; } 
    }

    return false;
}
