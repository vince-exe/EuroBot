#include "commands_utils.h"

int CommandsUtils::maxCoinLen = 10;

int CommandsUtils::idCreator = 0;

bool CommandsUtils::updateCommandAuth = false;

bool CommandsUtils::startCommandAuth = false;

bool CommandsUtils::startCommand = false;

bool CommandsUtils::settingsButtonClicked = false;

bool CommandsUtils::gameStarted = false;

std::string CommandsUtils::lastCommand;

bool CommandsUtils::isValidGroup(int64_t id) {
    std::string groupIdStr = JsonReader::getJsonObj()["groupId"];
    long long grouId = strtoll(groupIdStr.c_str(), NULL, 0); 

    return (id == grouId) ? true : false;
}

bool CommandsUtils::toInt(int* a, const std::string s) {
    try {
        *a = std::stoi(s);

        return true;
    }
    catch(std::invalid_argument const& ex) {
            return false;
        }
    catch(std::out_of_range const& ex) {
            return false;
        }
}

void CommandsUtils::printWinBet(TgBot::Bot* bot, int64_t id, int win, User* user) {
    std::string win_ = std::to_string(win);
    std::string money = std::to_string(user->getCoins());

    bot->getApi().sendMessage(
        id,
        "🤖 <b>Scommessa Effettuata</b> \
        \n\n✅ @" + user->getUsername() + " <i>ha vinto " + win_ +  " " + AdminSettings::getCoinName() + "</i> \
        \n\n💰 <b>Saldo Attuale</b>: " + money,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::printLoseBet(TgBot::Bot* bot, int64_t id, int lose, User* user) {
    std::string lose_ = std::to_string(lose);
    std::string money = std::to_string(user->getCoins());

    bot->getApi().sendMessage(
        id,
        "🤖 <b>Scommessa Effettuata</b> \
        \n\n❌ @" + user->getUsername() + " <i>ha perso " + lose_ +  " " + AdminSettings::getCoinName() + "</i> \
        \n\n💰 <b>Saldo Attuale</b>: " + money,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::fatalError(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id,
        "⛔ <b>System Error</b> \
        \n\n🤖 <i>Mi dispiace ho dovuto interrompere la partita per un errore di sistema.</i> \
        \n\n⚙️ <i>Il servizio riprenderà quando i tecnici avranno trovato una soluzione</i> \
        \n\n⛑️ <i>Cordiali saluti dallo staff di @scommesse_bot</i>",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

bool CommandsUtils::startBot(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user) {
    if(AdminSettings::size() != 0) { AdminSettings::clear(); }
    AdminSettings::init();

    /* if it's a private channel */
    if(id == user->user->id) { 
        CommandsUtils::printStartPrivatePanel(bot, id, user);

        return false;
    }
    
    if(!CommandsUtils::isValidGroup(id) || user->status != "creator") { return false; }

    CommandsUtils::startCommand = true;
    CommandsUtils::settingsButtonClicked = false;
    CommandsUtils::gameStarted = false;
    CommandsUtils::idCreator = user->user->id;

    return true;
}

void CommandsUtils::printAdminJoin(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user) {
    bot->getApi().editMessageText(
        "<b>👋 Ciao @" + user->user->username + "</b>\
        \n\n<i>🤖 Il bot è stato avviato con successo.</i> \
        \n\n<i>✏️ Un menu di impostazioni ti è stato inviato in privato </i>\
        \n\n<i>⚠️ Se il messaggio non è arrivato, assicurati di non aver bloccato il bot</i> \
        \n\n<i>✅ Utilizza il comando /join per entrare nella partita</i>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, std::make_shared<TgBot::GenericReply>()
    );
}

void CommandsUtils::printConfirmBoxReset(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "⚙️ <b>Pannello Conferma</b> \
        \n\n🤖 <i>Sei sicuro di voler ripristinare le impostazioni?</i>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printGameSettings(TgBot::Bot* bot, int64_t chatId) {
    bot->getApi().sendMessage(
        chatId,
        "🤖 <b>Impostazioni Partita</b> " \
        "\n\n<i>✏️ Non sarà possibile cambiare queste impostazioni fino alla prossima partita.</i>"
        "\n\n💰 <i>Soldi Iniziali</i>  " + AdminSettings::getValueByKey("SoldiIniziali") \
        + "\n\n🎩 <i>Scommesse Giornaliere</i>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("ScommesseGiornaliere"), "-1", {"♾", AdminSettings::getValueByKey("ScommesseGiornaliere")}) \
        + "\n\n🎁 <i>Regalo Soldi</i>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("RegaloSoldi"), "true", {"✅", "❌"}) \
        + "\n\n🥇 <i>Mostra Classifica</i>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("MostraClassifica"), "true", {"✅", "❌"}) \
        + "\n\n📉 <i>Percentuale Vittoria</i>  " + AdminSettings::getValueByKey("PercentualeVittoria") + " 💸" \
        + "\n\n📈 <i>Percentuale Sconfitta</i>  " + AdminSettings::getValueByKey("PercentualeSconfitta") + " 💸" \
        + "\n\n🪙 <i>Nome Valuta</i> " + AdminSettings::getValueByKey("NomeValuta"),
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::printGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard, bool isPrivate) {
    int64_t id = (isPrivate) ? user->user->id : query->message->chat->id;

    bot->getApi().sendMessage(
        id,
        "⚙️ <b>Pannello Generale</b>" \
        "\n\n🛠️ <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello generale del bot</i>" \
        "\n\n⚠️ <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>" \
        "\n\n✏️ <i>Una volta configurato il bot vai al pannello di avvio e premi il pulsante</i>  ✅Avvia",
        false, 0, keyboard, "HTML"
    );
}

void CommandsUtils::printInvalidArguments(TgBot::Bot* bot, TgBot::Message::Ptr message) {
    bot->getApi().sendMessage(
        message->chat->id,
        "⚠️ <b>Comando Invalido</b> \
        \n\n🤖 <i>Per favore inserisci impostazioni e valori esistenti</i>",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::editGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "⚙️ <b>Pannello Generale</b>" \
        "\n\n🛠️ <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello di configurazione del bot</i>" \
        "\n\n⚠️ <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>" \
        "\n\n✏️ <i>Una volta configurato il bot vai al pannello di avvio e premi il pulsante</i>  ✅Avvia",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printSettingsPanel(TgBot::Bot* bot, std::pair<int64_t, int32_t> ids, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "⚙️ <b>Pannello Configurazione</b> \n\n🛠️ <b>@scommesse_bot</b> <i>offre una vasta gamma di impostazioni, tutte da personalizzare</i>❗" \
        "\n\n💰 <b>Soldi Iniziali</b>  " + AdminSettings::getValueByKey("SoldiIniziali") \
        + "\n\n🎩 <b>Scommesse Giornaliere</b>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("ScommesseGiornaliere"), "-1", {"♾", AdminSettings::getValueByKey("ScommesseGiornaliere")}) \
        + "\n\n🎁 <b>Regalo Soldi</b>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("RegaloSoldi"), "true", {"✅", "❌"}) \
        + "\n\n🥇 <b>Mostra Classifica</b>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("MostraClassifica"), "true", {"✅", "❌"}) \
        + "\n\n📉 <b>Percentuale Vittoria</b>  " + AdminSettings::getValueByKey("PercentualeVittoria") + " 💸" \
        + "\n\n📈 <b>Percentuale Sconfitta</b>  " + AdminSettings::getValueByKey("PercentualeSconfitta") + " 💸" \
        + "\n\n🪙 <b>Nome Valuta</b> " + AdminSettings::getValueByKey("NomeValuta") \
        + "\n\n✏️  <i>Premi il pulsante</i> <b>/help</b> <i>per maggiori informazioni.</i>",
        ids.first,
        ids.second,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::editSettingsPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "⛑️ <b>Pannello Aiuto</b> \
        \n\n✏️ <i>Utilizza il comando /update \{impostazione\} \{valore\} per aggiornare un impostazione</i> \
        \n\n⛔ <i>Il nome dell'impostazione non deve contenere spazi. Es: \{SoldiIniziali\} \{1500\}</i> \
        \n\n⚙️ <b>Possibili Valori</b> \
        \n\n♾ = <b>-1</b> \
        \n\n✅ = <b>true</b> \
        \n\n❌ = <b>false</b>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printLoan(TgBot::Bot* bot, int64_t chatID, const std::string& donUsr, const std::string& recUsr, int money) {
    bot->getApi().sendMessage(
        chatID,
        "👑 <b>Prestito Effettuato</b> " \
        "\n\n🎩 L'utente @" + donUsr + " ha donato " + std::to_string(money) + " " + AdminSettings::getCoinName() + " a @" + recUsr \
        + "\n\n🪙 Questo si che è un atto di generosità",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    ); 
}

void CommandsUtils::printToS(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "<b>✏️ Termini & Condizioni </b> \
        \n\n⛔ <i>É consigliato l'utilizzo di questo bot solo ad un pubblico maggiorenne</i> \
        \n\n⚠️ <i>Il bot potrebbe causare dipendeza legata al gioco d'azzardo</i> \
        \n\n⛑️ <i>Gli sviluppatori non sono responsabili di eventuali patologie legate all'utilizzo di questo bot</i> \
        \n\n✅ Lo staff di @scommesse_bot ti augura buon divertimento :)",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printCopyRights(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "🧑‍💻 <b>Lista Sviluppatori</b>\n\n🥇 @bScreen <b>Programmer</b> \n\n🥈 @NonScopoMai <b>UI Designer</b>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printStartPanel(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().sendMessage(
        id,
        "⚙️ <b>Pannello Avvio</b> \
        \n\n👋🏻 <i>Ciao @" + user->user->username + "</i> \
        \n\n🤖 <i>@scommesse_bot è il bot più utilizzato dagli utenti di questa piattaforma per divertirsi in compagnia!</i> \
        \n\n🔧 <i>Per iniziare al meglio configura il bot e rendilo pronto per l'utilizzo</i>",
        false, 0, keyboard, "HTML"
    );     
}

void CommandsUtils::printStartPrivatePanel(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user) {
    bot->getApi().sendMessage(
        id,
        "⚙️ <b>Pannello Avvio</b> \
        \n\n👋🏻 <i>Ciao @" + user->user->username + " </i> \
        \n\n🤖 <i>@scommesse_bot è il bot più utilizzato dagli utenti di questa piattaforma per divertirsi in compagnia!</i> \
        \n\n⚠️  <i>Utilizza il comando /start nel gruppo dove hai invitato il bot per poter iniziare</i>",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );    
}

bool CommandsUtils::isValid(const std::string command, const std::string message) {
    if((command == "RegaloSoldi" || command == "MostraClassifica") && (message == "true" || message == "false")) { 
        return true; 
    }

    if(command == "SoldiIniziali" || command == "ScommesseGiornaliere") {
        try {
            int number = std::stoi(message);

            if(number == -1) { return true; }
        
            if(command == "ScommesseGiornaliere" && number <= 0) { return false; }
            return true;
        }
        catch(std::invalid_argument const& ex) {
            return false;
        }
        catch(std::out_of_range const& ex) {
            return false;
        }
    }

    if(command == "PercentualeVittoria" || command == "PercentualeSconfitta") {
        try {
            int money = std::stoi(message);

            if(money < 0 || money > 100) { return false; }

            return true;
        }
        catch(std::invalid_argument const& ex) {
            return false;
        }
        catch(std::out_of_range const& ex) {
            return false;
        }
    }

    if(command == "NomeValuta" && command.length() <= CommandsUtils::maxCoinLen) { 
        return true;
    }

    return false;
}

int CommandsUtils::countArguments(const std::string command, const std::string message) {
    int countArguments = 0;
    bool in = false;

    for(int i = command.length(); i < message.length(); i++) {
        while(message[i] != ' ' && i < message.length()) {
            in = true;
            i++;
        }
        if(in) { countArguments++; }
        in = false;
    }

    return countArguments;
}

std::vector<std::string> CommandsUtils::getArguments(const std::string command, const std::string message) {
    std::vector<std::string> argumentsList;
    std::string temp;

    for(int i = command.length(); i < message.length(); i++) {
        while(message[i] != ' ' && i < message.length()) {
            temp += message[i];
            i++;
        }
        if(temp.length()) { argumentsList.push_back(temp); }
        temp.clear();
    }

    return argumentsList;
}