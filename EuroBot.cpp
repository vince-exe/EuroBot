#include <iostream>
#include <fstream>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    std::ifstream ifs("configs/configs.json");
    json configsJson = json::parse(ifs);

    TgBot::Bot bot(configsJson["tokenBot"]);

    bot.getEvents().onCommand("start", [&bot, &configsJson](TgBot::Message::Ptr message) {
        if(message->from->username == configsJson["nicknameOwner"]) {
            bot.getApi().sendMessage(message->chat->id, "Hi!");
        }
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {

    });

    try {
        std::cout<<"\nBot " << bot.getApi().getMe()->username << " started"; 
        TgBot::TgLongPoll longPoll(bot);

        while (true) {
            std::cout<<"\n.";
            longPoll.start();
        }

    } catch (TgBot::TgException& e) {
        std::cout<<"\nerror: " << e.what();
    }

    return 0;
}