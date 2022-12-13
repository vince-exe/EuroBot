#include <iostream>
#include <fstream>
#include <vector>

#include <tgbot/tgbot.h>

#include "utils/utils.h"
#include "utils/ConfigsReader/configs_reader.h"

int main() {
    ConfigsReader::readJson("configs/configs.json");
    TgBot::Bot bot(ConfigsReader::configs["tokenBot"]);

    TgBot::InlineKeyboardMarkup::Ptr startKeyBoard(new TgBot::InlineKeyboardMarkup); 
    Utils::setKeyBoard(startKeyBoard, 
    {
        {"📖 Regolamento ", "regolamento"},
        {"© Developer ", "crediti"}
    }
    );
    Utils::setKeyBoard(startKeyBoard, {{"✅ Avvia", "avvia"}});
    
    bot.getEvents().onCommand("start", [&bot, &startKeyBoard](TgBot::Message::Ptr message) {
        std::string userStatus = bot.getApi().getChatMember(message->chat->id, message->from->id)->status;

        if(ConfigsReader::isAuthorizedRole(userStatus)) {
            std::string welc = "\n\n👋 *Benvenuto/a @" + message->from->username + "*";
            bot.getApi().sendMessage(
                message->chat->id,
                welc + "\n\n💰 _Scommetti & Vinci_ \n\n💬 Orientati con i pulsanti",
                false, 0, startKeyBoard, "MarkdownV2"
                );       
        }
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