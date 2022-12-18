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

    TgBot::InlineKeyboardMarkup::Ptr tempRules(new TgBot::InlineKeyboardMarkup);
    this->backRules = tempRules;

    TgBot::InlineKeyboardMarkup::Ptr tempSecondSettings(new TgBot::InlineKeyboardMarkup);
    this->secondSettingsBoard = tempSecondSettings;
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
        {"© Sviluppatori", "copyrights"},
        {"📖 Termini & Condizioni", "ToS"}
    }
    );

    Utils::setKeyBoard((this->settingsBoard), {{"🔧 Impostazioni", "settings"}});

    Utils::setKeyBoard((this->backBoardCopyrights), {{"🔙 Back", "backCopyRights"}});
    
    Utils::setKeyBoard((this->backRules), {{"🔙 Back", "backRules"}});

    Utils::setKeyBoard((this->secondSettingsBoard), 
    {
        {"⚙️ Ripristina", "resetSettings"},
        {"✅ Salva", "saveSettings"}
    }
    );
    Utils::setKeyBoard((this->secondSettingsBoard), {{"🔙 Back", "backRules"}});

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
        std::string groupIdStr = JsonReader::getJsonObj()["groupId"];
        long long grouId = strtoll(groupIdStr.c_str(), NULL, 0);  

        if(grouId != message->chat->id) { return; }

        if(user->status != "creator") { return; }
        Utils::idCreator = user->user->id;

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
        
        if(Utils::idCreator != user->user->id) { return; }
        
        try {
            if(query->data == "update_here") {
                this->bot->getApi().sendMessage(
                    query->message->chat->id,
                    "⚙️ <b>Pannello Configurazione</b>\n\n🛠️ <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello di configurazione del bot, configura il bot come meglio credi</i>\n\n⚠️ <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>\n\n✏️ Una volta configurato il bot vai al pannello di avvio e premi il pulsante  ✅Avvia\n\n✅ <b>Un saluto dallo staff di @scommesse_bot</b>",
                    false, 0, this->settingsBoard, "HTML"
                );
            }

            else if(query->data == "update_private") {
                this->bot->getApi().sendMessage(
                    user->user->id,
                    "🦺 <b>Pannello Configurazione</b>\n\n🔨 <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello di configurazione del bot</i>\n\n🛠️ <i>Configura il bot come meglio credi!!</i>\n\n⚠️ <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>\n\n✏️ Una volta configurato il bot vai al pannello di avvio e premi il pulsante ✅Avvia\n\n✅ <b>Un saluto dallo staff di @scommesse_bot</b>",
                    false, 0, this->settingsBoard, "HTML"
                );
            }

            else if(query->data == "backRules") {   
                this->bot->getApi().editMessageText(
                    "🦺 <b>Pannello Configurazione</b>\n\n🔨 <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello di configurazione del bot</i>\n\n🛠️ <i>Configura il bot come meglio credi!!</i>\n\n⚠️ <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>\n\n✏️ Una volta configurato il bot vai al pannello di avvio e premi il pulsante  ✅Avvia\n\n✅ <b>Un saluto dallo staff di @scommesse_bot</b>",
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "HTML", false, this->settingsBoard
                );
            }
    
            else if(query->data == "startGame") {
                ;
            }

            else if(query->data == "settings") {
                this->bot->getApi().editMessageText(
                    "👋🏻 Ciao <b> @" + user->user->username + "</b> \
                    \n\n🛠️ <b>@scommesse_bot</b> <i>offre una vasta gamma di impostazioni, tutte da personalizzare</i>❗" \
                    + "\n\n💰 <b>Soldi Iniziali</b>  " + AdminSettings::getValueByKey("startsMoney") \
                    + "\n\n🎩 <b>Scommesse Giornaliere</b>  " + Utils::getEmoji(AdminSettings::getValueByKey("dailyBets"), "-1", {"♾", "❌"}) \
                    + "\n\n🎁 <b>Regalo Soldi</b>  " + Utils::getEmoji(AdminSettings::getValueByKey("giveMoney"), "true", {"✅", "❌"}) \
                    + "\n\n🥇 <b>Mostra Classifica</b>  " + Utils::getEmoji(AdminSettings::getValueByKey("showClassification"), "true", {"✅", "❌"}) \
                    + "\n\n📉 <b>Percentuale Vittoria</b>  " + AdminSettings::getValueByKey("winPercentage") + " 💸" \
                    + "\n\n📈 <b>Percentuale Sconfitta</b>  " + AdminSettings::getValueByKey("losePercentage") + " 💸" \
                    + "\n\n🪙 <b>Nome Valuta</b> " + AdminSettings::getValueByKey("coinName") \
                    + "\n\n✏️  <i>Utilizza il comando /update \{impostazione\} \{valore\} per aggiornare un impostazione</i>" \
                    + "\n\n⚙️ <b>Possibili Valori</b>" \
                    + "\n\n♾ = <b>-1</b>" \
                    + "\n\n✅ = <b>true</b>" \
                    + "\n\n❌ = <b>false</b>", 
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "HTML", false, this->secondSettingsBoard
                );
            }

            else if(query->data == "ToS") {
                this->bot->getApi().editMessageText(
                    "<b>✏️ Termini & Condizioni </b>\n\n⛔ <i>É consigliato l'utilizzo di questo bot solo ad utenti maggiorenni</i>\n\n⚠️ <i>Il bot potrebbe causare dipendeza legata al gioco d'azzardo</i>\n\n⛑️ <i>Gli sviluppatori non sono responsabili di eventuali patologie legate all'utilizzo di questo bot</i>\n\n✅ Lo staff di @scommesse_bot ti augura buon divertimento :)",
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "HTML", false, this->backRules
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
                this->bot->getApi().editMessageText(
                    "🦺 <b>Pannello Configurazione</b>\n\n🔨 <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello di configurazione del bot</i>\n\n🛠️ <i>Configura il bot come meglio credi!!</i>\n\n⚠️ <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>\n\n✅ <b>Un saluto dallo staff di @scommesse_bot</b>",
                    query->message->chat->id,
                    query->message->messageId,
                    std::string(), "HTML", false, this->settingsBoard
                );
            }
        }
        catch(std::exception& e) {
            return;
        }
    });
}
