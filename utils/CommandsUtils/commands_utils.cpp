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
        "š¤ <b>Scommessa Effettuata</b> \
        \n\nā @" + user->getUsername() + " <i>ha vinto " + win_ +  " " + AdminSettings::getCoinName() + "</i> \
        \n\nš° <b>Saldo Attuale</b>: " + money,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::printLoseBet(TgBot::Bot* bot, int64_t id, int lose, User* user) {
    std::string lose_ = std::to_string(lose);
    std::string money = std::to_string(user->getCoins());

    bot->getApi().sendMessage(
        id,
        "š¤ <b>Scommessa Effettuata</b> \
        \n\nā @" + user->getUsername() + " <i>ha perso " + lose_ +  " " + AdminSettings::getCoinName() + "</i> \
        \n\nš° <b>Saldo Attuale</b>: " + money,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::fatalError(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id,
        "ā <b>System Error</b> \
        \n\nš¤ <i>Mi dispiace ho dovuto interrompere la partita per un errore di sistema.</i> \
        \n\nāļø <i>Il servizio riprenderĆ  quando i tecnici avranno trovato una soluzione</i> \
        \n\nāļø <i>Cordiali saluti dallo staff di @scommesse_bot</i>",
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
        "<b>š Ciao @" + user->user->username + "</b>\
        \n\n<i>š¤ Il bot ĆØ stato avviato con successo.</i> \
        \n\n<i>āļø Un menu di impostazioni ti ĆØ stato inviato in privato </i>\
        \n\n<i>ā ļø Se il messaggio non ĆØ arrivato, assicurati di non aver bloccato il bot</i> \
        \n\n<i>ā Utilizza il comando /join per entrare nella partita</i>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, std::make_shared<TgBot::GenericReply>()
    );
}

void CommandsUtils::printConfirmBoxReset(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "āļø <b>Pannello Conferma</b> \
        \n\nš¤ <i>Sei sicuro di voler ripristinare le impostazioni?</i>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printGameSettings(TgBot::Bot* bot, int64_t chatId) {
    bot->getApi().sendMessage(
        chatId,
        "š¤ <b>Impostazioni Partita</b> " \
        "\n\n<i>āļø Non sarĆ  possibile cambiare queste impostazioni fino alla prossima partita.</i>"
        "\n\nš° <i>Soldi Iniziali</i>  " + AdminSettings::getValueByKey("SoldiIniziali") \
        + "\n\nš© <i>Scommesse Giornaliere</i>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("ScommesseGiornaliere"), "-1", {"ā¾", AdminSettings::getValueByKey("ScommesseGiornaliere")}) \
        + "\n\nš <i>Regalo Soldi</i>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("RegaloSoldi"), "true", {"ā", "ā"}) \
        + "\n\nš„ <i>Mostra Classifica</i>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("MostraClassifica"), "true", {"ā", "ā"}) \
        + "\n\nš <i>Percentuale Vittoria</i>  " + AdminSettings::getValueByKey("PercentualeVittoria") + " šø" \
        + "\n\nš <i>Percentuale Sconfitta</i>  " + AdminSettings::getValueByKey("PercentualeSconfitta") + " šø" \
        + "\n\nšŖ <i>Nome Valuta</i> " + AdminSettings::getValueByKey("NomeValuta"),
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::printGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard, bool isPrivate) {
    int64_t id = (isPrivate) ? user->user->id : query->message->chat->id;

    bot->getApi().sendMessage(
        id,
        "āļø <b>Pannello Generale</b>" \
        "\n\nš ļø <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello generale del bot</i>" \
        "\n\nā ļø <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>" \
        "\n\nāļø <i>Una volta configurato il bot vai al pannello di avvio e premi il pulsante</i>  āAvvia",
        false, 0, keyboard, "HTML"
    );
}

void CommandsUtils::printInvalidArguments(TgBot::Bot* bot, TgBot::Message::Ptr message) {
    bot->getApi().sendMessage(
        message->chat->id,
        "ā ļø <b>Comando Invalido</b> \
        \n\nš¤ <i>Per favore inserisci impostazioni e valori esistenti</i>",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::editGeneralPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "āļø <b>Pannello Generale</b>" \
        "\n\nš ļø <i>Ciao @</i>" + user->user->username + " <i>benvenuto nel pannello di configurazione del bot</i>" \
        "\n\nā ļø <i>Le impostazioni vengono ripristinate ogni volta che il bot viene stoppato</i>" \
        "\n\nāļø <i>Una volta configurato il bot vai al pannello di avvio e premi il pulsante</i>  āAvvia",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printSettingsPanel(TgBot::Bot* bot, std::pair<int64_t, int32_t> ids, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "āļø <b>Pannello Configurazione</b> \n\nš ļø <b>@scommesse_bot</b> <i>offre una vasta gamma di impostazioni, tutte da personalizzare</i>ā" \
        "\n\nš° <b>Soldi Iniziali</b>  " + AdminSettings::getValueByKey("SoldiIniziali") \
        + "\n\nš© <b>Scommesse Giornaliere</b>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("ScommesseGiornaliere"), "-1", {"ā¾", AdminSettings::getValueByKey("ScommesseGiornaliere")}) \
        + "\n\nš <b>Regalo Soldi</b>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("RegaloSoldi"), "true", {"ā", "ā"}) \
        + "\n\nš„ <b>Mostra Classifica</b>  " + BotUtils::getEmoji(AdminSettings::getValueByKey("MostraClassifica"), "true", {"ā", "ā"}) \
        + "\n\nš <b>Percentuale Vittoria</b>  " + AdminSettings::getValueByKey("PercentualeVittoria") + " šø" \
        + "\n\nš <b>Percentuale Sconfitta</b>  " + AdminSettings::getValueByKey("PercentualeSconfitta") + " šø" \
        + "\n\nšŖ <b>Nome Valuta</b> " + AdminSettings::getValueByKey("NomeValuta") \
        + "\n\nāļø  <i>Premi il pulsante</i> <b>/help</b> <i>per maggiori informazioni.</i>",
        ids.first,
        ids.second,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::editSettingsPanel(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "āļø <b>Pannello Aiuto</b> \
        \n\nāļø <i>Utilizza il comando /update \{impostazione\} \{valore\} per aggiornare un impostazione</i> \
        \n\nā <i>Il nome dell'impostazione non deve contenere spazi. Es: \{SoldiIniziali\} \{1500\}</i> \
        \n\nāļø <b>Possibili Valori</b> \
        \n\nā¾ = <b>-1</b> \
        \n\nā = <b>true</b> \
        \n\nā = <b>false</b>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printUserStats(TgBot::Bot* bot, User& user, int64_t chatID, int nBets, std::pair<std::string, int> profit) {
    std::string text;
    if(profit.first == "n") { 
        text = "š @" + user.getUsername() + " non ha avuto nessun profitto dalle sue scommesse";
    }
    else if(profit.first == "win") {
        text = "š @" + user.getUsername() + " ha guadagnato " + std::to_string(profit.second) + " dalle sue scommesse";
    }
    else {
        text = "š @" + user.getUsername() + " ha perso " + std::to_string(profit.second) + " dalle sue scommesse";
    }

    bot->getApi().sendMessage(
        chatID,
        "\n\nš¤ <b>Statistiche in data</b>: " + BotUtils::currentDateTime("%d-%m-%Y") +  \
        "\n\nā <b>Id</b>: " + std::to_string(user.getId()) + \
        "\n\nš <b>Username</b>: @" + user.getUsername() + \
        "\n\nš° <b>" + AdminSettings::getCoinName() + "</b>: " + std::to_string(user.getCoins()) + \
        "\n\nš¬ <b>Numero Scommesse</b>: " + std::to_string(nBets) + \
        "\n\n" + text,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::cantGiveMoney(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id, 
        "š <b>Avviso Partita</b> \ 
        \n\nš¤ L'amministratore ha disattivato il prestito dei soldi per questa partita.",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::cantStake(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id, 
        "š <b>Avviso Partita</b> \ 
        \n\nš¤ Hai esaurito il numero di scommesse giornaliere",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::cantSeeClassification(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id,
        "š <b>Avviso Partita</b> \ 
        \n\nš¤ L'amministratore ha disattivato la classifica per questa partita.",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::printUsersList(TgBot::Bot* bot, int64_t id, std::vector<std::string>& usersList) {
    std::string text;
    int c = 0;
    for(auto &user : usersList) {
        if(c == 0) {  
            text += "\n\nš„ @" + user;
        }
        else if(c == 1) {
            text += "\n\nš„ @" + user;
        }
        else if(c == 2) {
            text += "\n\nš„ @" + user;
        }
        c++;
    }
    text += "\n\nš¬ Per avere maggiori informazioni utilizza il comando /stats.";
    bot->getApi().sendMessage(
        id,
        "š <b>Classifica Giocatori</b> " + text,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::noUserMsg(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id,
        "š¤ <i>La lista utenti ĆØ vuota</i>",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::printLoan(TgBot::Bot* bot, int64_t chatID, const std::string& donUsr, const std::string& recUsr, int money) {
    bot->getApi().sendMessage(
        chatID,
        "š <b>Prestito Effettuato</b> " \
        "\n\nš© L'utente @" + donUsr + " ha donato " + std::to_string(money) + " " + AdminSettings::getCoinName() + " a @" + recUsr \
        + "\n\nšŖ Questo si che ĆØ un atto di generositĆ ",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    ); 
}

void CommandsUtils::printToS(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "<b>āļø Termini & Condizioni </b> \
        \n\nā <i>Ć consigliato l'utilizzo di questo bot solo ad un pubblico maggiorenne</i> \
        \n\nā ļø <i>Il bot potrebbe causare dipendeza legata al gioco d'azzardo</i> \
        \n\nāļø <i>Gli sviluppatori non sono responsabili di eventuali patologie legate all'utilizzo di questo bot</i> \
        \n\nā Lo staff di @scommesse_bot ti augura buon divertimento :)",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printCopyRights(TgBot::Bot* bot, TgBot::CallbackQuery::Ptr query, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().editMessageText(
        "š§āš»Ā <b>Lista Sviluppatori</b>\n\nš„ @bScreen <b>Programmer</b> \n\nš„ @NonScopoMai <b>UI Designer</b>",
        query->message->chat->id,
        query->message->messageId,
        std::string(), "HTML", false, keyboard
    );
}

void CommandsUtils::printStartPanel(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user, TgBot::InlineKeyboardMarkup::Ptr keyboard) {
    bot->getApi().sendMessage(
        id,
        "āļø <b>Pannello Avvio</b> \
        \n\nšš» <i>Ciao @" + user->user->username + "</i> \
        \n\nš¤ <i>@scommesse_bot ĆØ il bot piĆ¹ utilizzato dagli utenti di questa piattaforma per divertirsi in compagnia!</i> \
        \n\nš§ <i>Per iniziare al meglio configura il bot e rendilo pronto per l'utilizzo</i>",
        false, 0, keyboard, "HTML"
    );     
}

void CommandsUtils::printStartPrivatePanel(TgBot::Bot* bot, int64_t id, TgBot::ChatMember::Ptr user) {
    bot->getApi().sendMessage(
        id,
        "āļø <b>Pannello Avvio</b> \
        \n\nšš» <i>Ciao @" + user->user->username + " </i> \
        \n\nš¤ <i>@scommesse_bot ĆØ il bot piĆ¹ utilizzato dagli utenti di questa piattaforma per divertirsi in compagnia!</i> \
        \n\nā ļø  <i>Utilizza il comando /start nel gruppo dove hai invitato il bot per poter iniziare</i>",
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

void CommandsUtils::historyBets(TgBot::Bot* bot, int64_t chatID, const std::string& date, std::vector<Bet>& bets, std::string username) {
    std::string text;
    std::string text1;
    int cWin = 0;
    int sumCoins = 0;
    for(auto& bet : bets) {
        text +="\n\nš <b>Id:</b> " + std::to_string(bet.getId()) + "\nš° <b>Valore:</b> " + std::to_string(bet.getMoney()) + "<b>" + BotUtils::getEmoji(std::to_string(bet.getState()), "1", {"\nā Vinta", "\nā Persa"}) + "</b>";
        if(bet.getState()) { cWin++; }
        sumCoins += bet.getMoney();
    }
    
    if((bets.size() - cWin) == cWin) {
        text1 += "š¤ Sembra che la situazione fosse pari";
    }
    else if((bets.size() - cWin) > cWin) {
        text1 += "š¤ Situazione abbastanza scomoda";
    }
    else {
        text1 += "š¤ Wow ottimo risultato";
    }
    bot->getApi().sendMessage(
        chatID, 
        "š® <b>Cronologia Scommesse</b> " + date + " " + \
        text,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
    
    bot->getApi().sendMessage(
        chatID,
        "š <b>Riepilogo Cronologia</b> \
        \n\nāļø <b>Utente:</b> @" + username + " " + \
        "\n\nā <b>Scommesse Perse:</b> " + std::to_string(bets.size() - cWin) + \
        "\n\nā <b>Scommesse Vinte:</b> " + std::to_string(cWin) + \
        "\n\nš° <b>Totale Denaro:</b> " + std::to_string(sumCoins) + \
        "\n\n" + text1,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::historyLoans(TgBot::Bot* bot, int64_t chatID, const std::string& date, std::vector<Loan>& loans, std::string username) {
    std::string text;
    std::string text1;
    int numLoans = 0;
    for(auto& loan : loans) {
        text +="\n\nš <b>Id:</b> " + std::to_string(loan.getId()) + "\nš° <b>Valore:</b> " + std::to_string(loan.getCoins()) + "\nš <b>Utente:</b> " + loan.getRecUsr();
        numLoans++;
    }
    
    if(numLoans >= 6) {
        text1 += "š Si respira generositĆ  nell'aria";
    }
    else {
        text1 += "š¤ A quanto pare a qualcuno non piace prestare soldi";
    }
    bot->getApi().sendMessage(
        chatID, 
        "š¬ <b>Cronologia Prestiti</b> " + date + " " + \
        text,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
    
    bot->getApi().sendMessage(
        chatID,
        "š <b>Riepilogo Cronologia</b> \
        \n\nāļø <b>Donatore:</b> @" + username + " " + \
        "\n\nš® <b>Prestiti Totali:</b> " + std::to_string(numLoans) + " " + \
        "\n\n" + text1,
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::noBets(TgBot::Bot* bot, int64_t chatID, std::string& date, bool anotherUser, const std::string& username) {
    if(date == BotUtils::currentDateTime("%Y-%m-%d")) {
        date = "oggi";
    }
    else {
        std::string tmp = date;
        date = "il " + tmp;
    }
    if(anotherUser) {
        bot->getApi().sendMessage(
            chatID,
            "š® L'utente @" + username + " non ha effettuato nessuna scommessa " + date
        );
        return;
    }
    bot->getApi().sendMessage(
        chatID,
        "š® Non hai effettuato nessuna scommessa " + date + \
        "\n\nš¤ Utilizza il comando /punta per effettuare una scommessa"
    );
}

void CommandsUtils::noLoans(TgBot::Bot* bot, int64_t chatID, std::string& date, bool anotherUser, const std::string& username) {
    if(date == BotUtils::currentDateTime("%Y-%m-%d")) {
        date = "oggi";
    }
    else {
        std::string tmp = date;
        date = "il " + tmp;
    }
    if(anotherUser) {
        bot->getApi().sendMessage(
            chatID,
            "š¬ L'utente @" + username + " non ha effettuato nessun prestito " + date
        );
        return;
    }
    bot->getApi().sendMessage(
        chatID,
        "š¬ Non hai effettuato nessun prestito " + date + \
        "\n\nš¤ Utilizza il comando /presta per effettuare un prestito"
    );
}

void CommandsUtils::helpCommand(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id,
        "<b>š¬ Lista Comandi</b> \
        \n\nāļø <b>/join</b> ti fa entrare in partita \
        \n\nš <b>/infoGame</b> ti restituisce le impostazioni che l'admin ha usato per la partita \
        \n\nāļø <b>/punta</b> \{soldi\} ti fa scommettere i soldi desiderati \
        \n\nš <b>/presta</b> \{@utente\} \{soldi\} ti fa prestare i soldi desiderati \
        \n\nāļø <b>/stats</b> \{@utente\} ti mostra le tue statistiche o quelle di un'utente se inserito nel comando \
        \n\nš <b>/classifica</b> ti mostra la top 3 giocatori con piĆ¹ soldi della partita \
        \n\nāļø <b>/cronScommesse</b> \{@utente\} \{data\} ti mostra la tua cronologia scommesse oppure quella di un utente se inserito nel comando \
        \n\nš <b>/cronPrestiti</b> \{@utente\} \{data\} ti mostra la tua cronologia prestiti oppure quella di un utente se inserito nel comando \
        \n\nš <i>la data deve essere nel seguente formato \{ Anno / Mese / Giorno \} oppure puoi usare \{oggi\}</i> \
        \n\nā <i>I comandi /cronScommesse /cronPrestiti /infoGame richiedono che tu abbia avviato il bot in privato</i> \
        \n\nāļø <i>Per ottenere maggiori informazioni puoi rivolgerti allo staff di @scommesse_bot</i>",
        false, 0, std::make_shared<TgBot::GenericReply>(), "HTML"
    );
}

void CommandsUtils::cantHelp(TgBot::Bot* bot, int64_t id) {
    bot->getApi().sendMessage(
        id,
        "š Invio Fallito \
        \n\nš¤ Avvia il bot in privato per ricevere questo messaggio"
    );
}