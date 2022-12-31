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

int BotUtils::getRandom(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max); 

    return  dist6(rng);
}

void BotUtils::printFatalErrorDB(DBErrors::SqlErrors* sqlErr) {
    std::cout<<"\nERROR: " << sqlErr->what;
    std::cout<<"\nSTATUS: " << sqlErr->sqlState;
    std::cout<<"\nERR-CODE: " << sqlErr->errCode;
}

const std::string BotUtils::currentDateTime(const std::string& format) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), format.c_str(), &tstruct);

    return buf;
}

std::pair<std::string, int> BotUtils::getProfit(std::vector<Bet>& bets) {
    int goodProfit = 0, badProfit = 0;
    for(auto bet : bets) { 
        if(bet.getState()) { goodProfit += (bet.getMoney() * AdminSettings::getWinPercentage()) / 100;}
        else { badProfit += (bet.getMoney() * AdminSettings::getLosePercentage()) / 100; }
    }

    if(goodProfit == badProfit) { return {"n", 0}; }
    
    if(goodProfit > badProfit) { return {"win", goodProfit - badProfit}; }

    return {"lose", badProfit - goodProfit};
}