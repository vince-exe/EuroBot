#include "bot_commands.h"

BotCommands::BotCommands(TgBot::Bot* bot) {
    this->bot = bot;
    this->eventBroadCaster = &this->bot->getEvents();
   
    TgBot::InlineKeyboardMarkup::Ptr tempBack(new TgBot::InlineKeyboardMarkup);
    this->backBoardCopyrights = tempBack;

    TgBot::InlineKeyboardMarkup::Ptr tempSettings(new TgBot::InlineKeyboardMarkup);
    this->settingsBoard = tempSettings;
}

BotCommands::~BotCommands() {
    delete this->eventBroadCaster;
}

void BotCommands::init() {

    Utils::setKeyBoard((this->settingsBoard),
    {
        {"🔧 Impostazioni", " settings"}, 
        {"© Developers", "copyrights"},
        {"📖 Regolamento", "rules"}
    }
    );
    Utils::setKeyBoard((this->settingsBoard), {{"✅ Avvia", "startGame"}});
    
    Utils::setKeyBoard((this->backBoardCopyrights), {{"🔙 Back", "backCopyRights"}});
    
    this->start();
    this->callBackQuery();
}

void BotCommands::start() {
    this->eventBroadCaster->onCommand("start", [this](TgBot::Message::Ptr message) {
    
        std::string userStatus = this->bot->getApi().getChatMember(message->chat->id, message->from->id)->status;

        if(userStatus != "creator") { return; }
        
        bot->getApi().sendMessage(
            message->chat->id,
            "*start message*",
            false, 0, this->settingsBoard, "Markdown"    
        );
    });
}

void BotCommands::callBackQuery() {
    this->bot->getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {

        std::string userStatus = this->bot->getApi().getChatMember(query->message->chat->id, query->from->id)->status;
        if(userStatus != "creator") { return; }
        
        try {
            if(query->data == "startGame") {
                ;
            }

            else if(query->data == "copyrights") {
                this->bot->getApi().editMessageText(
                    "🧑‍💻 *Lista Sviluppatori*\n\n🥇 @bScreen *Programmer* \n\n🥈 @NonScopoMai *UI Designer*",
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "Markdown", false, this->backBoardCopyrights
                );
            }

            else if(query->data == "backCopyRights") {
                this->bot->getApi().editMessageText(
                    "*start message*",
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "Markdown", false, this->settingsBoard
                );
            }
        }
        catch(std::exception& e) {
            return;
        }
    });
}
