#include "utils.h"

void Utils::setKeyBoard(TgBot::InlineKeyboardMarkup::Ptr& keyboard, const std::vector<std::pair<std::string, std::string>> vec) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;

    for(auto it : vec) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);

        button->text = it.first;
        button->callbackData = it.second;

        row.push_back(button);
    }

    keyboard->inlineKeyboard.push_back(row);
}