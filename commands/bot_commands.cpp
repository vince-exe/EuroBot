#include "bot_commands.h"

BotCommands::BotCommands(TgBot::Bot* bot) {
    this->bot = bot;
    this->eventBroadCaster = &this->bot->getEvents();
    
    TgBot::InlineKeyboardMarkup::Ptr tempStart(new TgBot::InlineKeyboardMarkup);
    this->startKeyBoard = tempStart;

    TgBot::InlineKeyboardMarkup::Ptr tempBack(new TgBot::InlineKeyboardMarkup);
    this->backBoardCopyrights = tempBack;

    TgBot::InlineKeyboardMarkup::Ptr tempSettings(new TgBot::InlineKeyboardMarkup);
    this->settingsBoard = tempSettings;
}

BotCommands::~BotCommands() {
    delete this->eventBroadCaster;
}

void BotCommands::init() {
    Utils::setKeyBoard((this->startKeyBoard),
    {
        {"🔑 Configura Qui", "update_here"},
        {"🔐 Configura In Privato", "update_private"}
    }
    );
    Utils::setKeyBoard((this->startKeyBoard),
    {
        {"✅ Avvia", "startGame"}
    }
    );

    Utils::setKeyBoard((this->settingsBoard),
    {
        {"🔧 Impostazioni", " settings"}, 
        {"© Sviluppatori", "copyrights"},
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
        TgBot::ChatMember::Ptr user = this->bot->getApi().getChatMember(message->chat->id, message->from->id);
        
        /* if it's a private channel */
        if(message->chat->id == user->user->id) { 
            this->bot->getApi().sendMessage(
                message->chat->id,
                "👋🏻 Ciao " + user->user->username + "\n\n@scommesse_bot è il bot più utilizzato dagli utenti di questa piattaforma per divertirsi in compagnia!!\n\n⚠️  <i>Utilizza il comando /start nel gruppo dove hai invitato il bot per poter iniziare</i>",
                false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
            );

            return;
        }

        if(user->status != "creator") { return; }
        Utils::hasAccess = true;

        this->bot->getApi().sendMessage(
            message->chat->id,
            "👋🏻 Ciao " + user->user->username + "\n\n@scommesse_bot è il bot più utilizzato dagli utenti di questa piattaforma per divertirsi in compagnia!!\n\n🔧  <i>Per iniziare al meglio configura il bot e rendilo pronto per l'utilizzo</i>\n\n✏️  <i>Se nessuna modifica verrà effettuata il bot utilizzerà le impostazioni di default</i>",
            false, 0, this->startKeyBoard, "HTML"
        );
    });
}

void BotCommands::callBackQuery() {
    this->bot->getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        TgBot::ChatMember::Ptr user = this->bot->getApi().getChatMember(query->message->chat->id, query->from->id);
        
        try {
            if(query->data == "update_here") {

            }

            else if(query->data == "update_private") {
                this->bot->getApi().sendMessage(
                user->user->id,
                "ehyyyy",
                false,
                0
                );
            }

            else if(query->data == "startGame") {
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
