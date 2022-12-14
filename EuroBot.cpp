#include <iostream>
#include <fstream>
#include <vector>

#include <tgbot/tgbot.h>

#include "commands/bot_commands.h"
#include "utils/utils.h"

int main() {
    JsonObjs::configs.setPath("configs/configs.json");
    TgBot::Bot bot(JsonObjs::configs.getJsonObj()["tokenBot"]);

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