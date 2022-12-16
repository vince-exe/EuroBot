#include "bot_commands.h"

BotCommands::BotCommands(TgBot::Bot* bot) {
    this->bot = bot;

    this->eventBroadCaster = new TgBot::EventBroadcaster;
    this->eventBroadCaster = &this->bot->getEvents();

    TgBot::InlineKeyboardMarkup::Ptr tempPlay(new TgBot::InlineKeyboardMarkup); 
    this->playKeyBoard = tempPlay;
    
    TgBot::InlineKeyboardMarkup::Ptr tempBack(new TgBot::InlineKeyboardMarkup);
    this->backBoardCopyrights = tempBack;

    TgBot::InlineKeyboardMarkup::Ptr tempSettings(new TgBot::InlineKeyboardMarkup);
    this->settingsBoard = tempSettings;
}

BotCommands::~BotCommands() {
    delete this->eventBroadCaster;
}

void BotCommands::init() {

    Utils::setKeyBoard((this->playKeyBoard), 
    {
        {"📖 Regolamento ", "rules"},
        {"© Developer ", "copyrights"}
    }
    );
    Utils::setKeyBoard((this->playKeyBoard), {{"🔙 Back", "backToSettings"}});
    Utils::setKeyBoard((this->playKeyBoard), {{"✅ Avvia", "start"}});
    
    Utils::setKeyBoard((this->backBoardCopyrights), {{"🔙 Back", "backCopyRights"}});

    Utils::setKeyBoard((this->settingsBoard),
    {
        {"🔧 Impostazioni", " settings"},
        {"✅ Avvia", "startGame"}
    }
    );
    
    this->start();
    this->callBackQuery();
}

void BotCommands::start() {
    this->eventBroadCaster->onCommand("start", [this](TgBot::Message::Ptr message) {
        Utils::startCmdTyped = true;

        std::string userStatus = this->bot->getApi().getChatMember(message->chat->id, message->from->id)->status;

        if(userStatus != "creator") { return; }
        
        std::string welc = "\n\n👋 *Benvenuto/a " + message->from->username + "*";
        
        bot->getApi().sendMessage(
            message->chat->id,
            welc + "\n\n🔧 *Impostazioni:* _Modifica le impostazioni della partita_\n\n✏️ *Nota:* _Le modifiche sono di base default_",
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
                std::string welc = "\n\n👋 *Pronto a giocare? " + query->message->from->username + "*";

                this->bot->getApi().editMessageText(
                    welc + "\n\n💰 _Scommetti & Vinci_ \n\n💬 Orientati con i pulsanti",
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "Markdown", false, this->playKeyBoard
                );
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
                std::string welc = "\n\n👋 *Pronto a giocare? " + query->message->from->username + "*";

                this->bot->getApi().editMessageText(
                    welc + "\n\n💰 _Scommetti & Vinci_ \n\n💬 Orientati con i pulsanti",
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "Markdown", false, this->playKeyBoard
                );
            }

            else if(query->data == "backToSettings") {
                std::string welc = "\n\n👋 *Benvenuto/a " + query->message->from->username + "*";

                this->bot->getApi().editMessageText(
                    welc + "\n\n🔧 *Impostazioni:* _Modifica le impostazioni della partita_\n\n✏️ *Nota:* _Le modifiche sono di base default_",
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
