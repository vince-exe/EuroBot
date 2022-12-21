#include "utils.h"

void CommandsUtils::printConfirmBoxReset(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "⚙️ <b>Pannello Conferma</b> \
        \n\n🤖 <i>Sei sicuro di voler ripristinare le impostazioni?</i>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
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
        "❌ <b>Invalid Command</b> ❌",
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

void CommandsUtils::printSettingsPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "⚙️ <b>Pannello Configurazione</b> \n\n🛠️ <b>@scommesse_bot</b> <i>offre una vasta gamma di impostazioni, tutte da personalizzare</i>❗" \
        "\n\n💰 <b>Soldi Iniziali</b>  " + AdminSettings::getValueByKey("SoldiIniziali") \
        + "\n\n🎩 <b>Scommesse Giornaliere</b>  " + Utils::getEmoji(AdminSettings::getValueByKey("ScommesseGiornaliere"), "-1", {"♾", AdminSettings::getValueByKey("ScommesseGiornaliere")}) \
        + "\n\n🎁 <b>Regalo Soldi</b>  " + Utils::getEmoji(AdminSettings::getValueByKey("RegaloSoldi"), "true", {"✅", "❌"}) \
        + "\n\n🥇 <b>Mostra Classifica</b>  " + Utils::getEmoji(AdminSettings::getValueByKey("MostraClassifica"), "true", {"✅", "❌"}) \
        + "\n\n📉 <b>Percentuale Vittoria</b>  " + AdminSettings::getValueByKey("PercentualeVittoria") + " 💸" \
        + "\n\n📈 <b>Percentuale Sconfitta</b>  " + AdminSettings::getValueByKey("PercentualeSconfitta") + " 💸" \
        + "\n\n🪙 <b>Nome Valuta</b> " + AdminSettings::getValueByKey("NomeValuta") \
        + "\n\n✏️  <i>Premi il pulsante</i> <b>/help</b> <i>per maggiori informazioni.</i>",
        query->message->chat->id,
        query->message->messageId,
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

void CommandsUtils::printStartPanel(TgBot::Bot* bot, TgBot::Message::Ptr message, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().sendMessage(
        message->chat->id,
        "⚙️ <b>Pannello Avvio</b> \
        \n\n👋🏻 <i>Ciao @" + user->user->username + "</i> \
        \n\n🤖 <i>@scommesse_bot è il bot più utilizzato dagli utenti di questa piattaforma per divertirsi in compagnia!</i> \
        \n\n🔧 <i>Per iniziare al meglio configura il bot e rendilo pronto per l'utilizzo</i>",
        false, 0, keyboard, "HTML"
    );     
}

void CommandsUtils::printStartPrivatePanel(TgBot::Bot* bot, TgBot::Message::Ptr message, TgBot::ChatMember::Ptr user) {
    bot->getApi().sendMessage(
        message->chat->id,
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

void Utils::setKeyBoard(TgBot::InlineKeyboardMarkup::Ptr keyboard, const std::vector<std::pair<std::string, std::string>> vec) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> row;

    for(auto it : vec) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);

        button->text = it.first;
        button->callbackData = it.second;

        row.push_back(button);
    }

    keyboard->inlineKeyboard.push_back(row);
}

std::string Utils::getEmoji(const std::string s, const std::string condition, const std::pair<std::string, std::string> emoji) {
    return (s == condition ) ? emoji.first : emoji.second;
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