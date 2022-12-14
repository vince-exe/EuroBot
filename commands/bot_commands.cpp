#include "bot_commands.h"

BotCommands::BotCommands(TgBot::Bot* bot) {
    this->bot = bot;

    this->eventBroadCaster = new TgBot::EventBroadcaster;
    this->eventBroadCaster = &this->bot->getEvents();

    TgBot::InlineKeyboardMarkup::Ptr temp(new TgBot::InlineKeyboardMarkup); 
    this->startKeyBoard = temp;
}

BotCommands::~BotCommands() {
    delete this->eventBroadCaster;
}

void BotCommands::init() {

    Utils::setKeyBoard((this->startKeyBoard), 
    {
        {"📖 Regolamento ", "rules"},
        {"© Developer ", "copyrights"}
    }
    );
    Utils::setKeyBoard((this->startKeyBoard), {{"✅ Avvia", "start"}});
    
    this->start();
    this->callBackQuery();
}

TgBot::InlineKeyboardMarkup::Ptr BotCommands::getStartKeyBoard() {
    return this->startKeyBoard;
}

void BotCommands::start() {
    this->eventBroadCaster->onCommand("start", [this](TgBot::Message::Ptr message) {
        std::string userStatus = this->bot->getApi().getChatMember(message->chat->id, message->from->id)->status;

        if(userStatus == "creator") {
            std::string welc = "\n\n👋 *Benvenuto/a @" + message->from->username + "*";
            this->bot->getApi().sendMessage(
                message->chat->id,
                welc + "\n\n💰 _Scommetti & Vinci_ \n\n💬 Orientati con i pulsanti",
                false, 0, this->getStartKeyBoard(), "MarkdownV2"
                );       
        }
    });
}

void BotCommands::callBackQuery() {
    this->bot->getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        if(query->data == "copyrights") {
            this->bot->getApi().sendMessage(
                query->message->chat->id,
                "🧑‍💻 *Lista Sviluppatori*\n\n🥇 @bScreen *[* Programmer *]* \n\n🥈 @NonScopoMai *[* UI Designer *]*",
                false, 0, 0, "MarkdownV2"
                );
            }
    });
}