#include <iostream>
#include <fstream>
#include <vector>

#include <tgbot/tgbot.h>

#include "commands/bot_commands.h"
#include "database/database.h"
#include "utils/JsonReader/json_reader.h"
#include "utils/AdminSettings/admin_settings.h"


int main() {
    JsonReader::read("configs/configs.json");

    if(!DBUtils::startDatabase(JsonReader::getJsonObj()["hostNameDB"], JsonReader::getJsonObj()["user"], JsonReader::getJsonObj()["password"], JsonReader::getJsonObj()["schemaDB"])) {
        return EXIT_FAILURE;
    };    

    TgBot::Bot bot(JsonReader::getJsonObj()["tokenBot"]);
        
    AdminSettings::init();

    BotCommands botCommands(&bot);
    botCommands.init();

    try {
        std::cout<<"\n\nBot " << bot.getApi().getMe()->username << " started"; 
        TgBot::TgLongPoll longPoll(bot);

        while (true) {
            std::cout<<"\n.";
            longPoll.start();
        }

    } catch (TgBot::TgException& e) {
        std::cout<<"\nerror: " << e.what();
    }

    Database::destroy();
    
    return EXIT_SUCCESS;
}