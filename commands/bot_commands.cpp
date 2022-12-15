#include "bot_commands.h"

BotCommands::BotCommands(TgBot::Bot* bot) {
    this->bot = bot;

    this->eventBroadCaster = new TgBot::EventBroadcaster;
    this->eventBroadCaster = &this->bot->getEvents();

    TgBot::InlineKeyboardMarkup::Ptr tempPlay(new TgBot::InlineKeyboardMarkup); 
    this->playKeyBoard = tempPlay;
    
    TgBot::InlineKeyboardMarkup::Ptr tempBack(new TgBot::InlineKeyboardMarkup);
    this->backBoardCopyrights = tempBack;
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
    Utils::setKeyBoard((this->playKeyBoard), {{"✅ Avvia", "start"}});
    
    Utils::setKeyBoard((this->backBoardCopyrights), {{"🔙 Back", "backCopyRights"}});

    this->start();
    this->play();
    this->callBackQuery();
}

TgBot::InlineKeyboardMarkup::Ptr BotCommands::getPlayKeyBoard() {
    return this->playKeyBoard;
}

TgBot::InlineKeyboardMarkup::Ptr BotCommands::getBackCopyRightsBoard() {
    return this->backBoardCopyrights;
}

void BotCommands::start() {
    this->eventBroadCaster->onCommand("start", [this](TgBot::Message::Ptr message) {
        std::string userStatus = this->bot->getApi().getChatMember(message->chat->id, message->from->id)->status;

        if(userStatus != "creator") { return; }

        bot->getApi().sendMessage(message->chat->id, "questo è un messaggio!!");
    });
}

void BotCommands::play() {
    this->eventBroadCaster->onCommand("play", [this](TgBot::Message::Ptr message) {
        std::string userStatus = this->bot->getApi().getChatMember(message->chat->id, message->from->id)->status;

        if(userStatus != "creator") { return; }
        
        std::string welc = "\n\n👋 *Pronto a giocare? " + message->from->username + "*";

        this->bot->getApi().sendMessage(
            message->chat->id,
            welc + "\n\n💰 _Scommetti & Vinci_ \n\n💬 Orientati con i pulsanti",    
            false, 0, this->getPlayKeyBoard(), "MarkdownV2"
        );       
    });
}

void BotCommands::callBackQuery() {
    this->bot->getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        if(query->data == "copyrights") {
            this->bot->getApi().editMessageText(
                "🧑‍💻 *Lista Sviluppatori*\n\n🥇 @bScreen *[* Programmer *]* \n\n🥈 @NonScopoMai *[* UI Designer *]*",
                query->message->chat->id,
                query->message->messageId,
                "", "MarkdownV2", false, this->getBackCopyRightsBoard()
            );
        }
        /* DOESN'T WORK
        else if(query->data == "backCopyRights") {
            std::string welc = "\n\n👋 *Pronto a giocare? " + query->message->from->username + "*";
            this->bot->getApi().editMessageText(
                welc + "\n\n💰 _Scommetti & Vinci_ \n\n💬 Orientati con i pulsanti",
                query->message->chat->id,
                query->message->messageId,
                "",
                "",
                false,
                this->getPlayKeyBoard()
            );
        }
        */
    });
}
