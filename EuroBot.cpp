#include <iostream>
#include <fstream>
#include <vector>

#include <tgbot/tgbot.h>

#include "commands/bot_commands.h"
#include "utils/JsonReader/json_reader.h"
#include "utils/AdminSettings/admin_settings.h"

int main() {
    JsonReader::read("configs/configs.json");
    TgBot::Bot bot(JsonReader::getJsonObj()["tokenBot"]);

    AdminSettings::init();

    BotCommands botCommands(&bot);
    botCommands.init();
    
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