#include "bot_commands.h"

BotCommands::BotCommands(TgBot::Bot* bot) {
    this->bot = bot;
    this->eventBroadCaster = &this->bot->getEvents();
    
    TgBot::InlineKeyboardMarkup::Ptr startKeyBoard(new TgBot::InlineKeyboardMarkup);
    this->startKeyBoard = startKeyBoard;

    TgBot::InlineKeyboardMarkup::Ptr generalBoard(new TgBot::InlineKeyboardMarkup);
    this->generalBoard = generalBoard;

    TgBot::InlineKeyboardMarkup::Ptr settingsBoard(new TgBot::InlineKeyboardMarkup);
    this->settingsBoard = settingsBoard;

    TgBot::InlineKeyboardMarkup::Ptr backToStartPanel(new TgBot::InlineKeyboardMarkup);
    this->backToStartPanel = backToStartPanel;
    
    TgBot::InlineKeyboardMarkup::Ptr backToSettings(new TgBot::InlineKeyboardMarkup);
    this->backToSettings = backToSettings;

    TgBot::InlineKeyboardMarkup::Ptr confirmBoard(new TgBot::InlineKeyboardMarkup);
    this->confirmBoard = confirmBoard;
}

BotCommands::~BotCommands() {
    delete this->eventBroadCaster;
}

void BotCommands::init() {
    BotUtils::setKeyBoard((this->startKeyBoard),
    {
        {"🔑 Configura Qui", "update_here"},
        {"🔐 Configura In Privato", "update_private"}
    }
    );
    BotUtils::setKeyBoard((this->startKeyBoard),
    {
        {"✅ Avvia", "startGame"}
    }
    );

    BotUtils::setKeyBoard((this->generalBoard),
    {
        {"© Sviluppatori", "copyrights"},
        {"📖 Termini & Condizioni", "ToS"}
    }
    );
    BotUtils::setKeyBoard((this->generalBoard), {{"🔧 Impostazioni", "settings"}});

    BotUtils::setKeyBoard((this->backToStartPanel), {{"🔙 Back", "backToStartPanel"}});

    BotUtils::setKeyBoard((this->settingsBoard), {{"⚙️ Ripristina", "resetSettings"}});

    BotUtils::setKeyBoard((this->settingsBoard),
    {
        {"🔙 Back", "backToStartPanel"},
        {"🆘 Help", "helpSettings"}
    }
    );

    BotUtils::setKeyBoard((this->backToSettings), {{"🔙 Back", "backToSettings"}});

    BotUtils::setKeyBoard((this->confirmBoard), 
    {
        {"❌ Annulla", "deny"},
        {"✅ Conferma", "confirm"}
    }
    );

    this->start();
    this->update();
    this->join();
    this->callBackQuery();
}

void BotCommands::start() {
    this->eventBroadCaster->onCommand("start", [this](TgBot::Message::Ptr message) {
        TgBot::ChatMember::Ptr user = this->bot->getApi().getChatMember(message->chat->id, message->from->id);

        CommandsUtils::lastCommand = "start";
        
        if(CommandsUtils::startCommand) {
            if(!CommandsUtils::isValidGroup(message->chat->id)) { return; }

            this->bot->getApi().sendMessage(
                message->chat->id,
                "<b>⛔ Hai ancora una sessione attiva, desideri chiuderla? </b>",
                false, 0, this->confirmBoard, "HTML"
            );
            return;
        }
        if(CommandsUtils::startBot(this->bot, message->chat->id, user)) {
            CommandsUtils::printStartPanel(this->bot, message->chat->id, user, this->startKeyBoard);
        };
    });
}
    
void BotCommands::update() {
    this->eventBroadCaster->onCommand("update", [this](TgBot::Message::Ptr message) {
        if(!CommandsUtils::updateCommandAuth || message->from->id != CommandsUtils::idCreator) { return; }

        if(CommandsUtils::countArguments("/update", message->text) != 2) { 
            CommandsUtils::printInvalidArguments(this->bot, message);
            return;
        }
        std::vector<std::string> args = CommandsUtils::getArguments("/update", message->text);

        if(!AdminSettings::exist(args[0]) || !CommandsUtils::isValid(args[0], args[1])) { 
            CommandsUtils::printInvalidArguments(this->bot, message);
            return;
        }
        
        std::string tmp = AdminSettings::getValueByKey(args[0]);
        AdminSettings::setKeyValue(args[0], args[1]);

        if(tmp != AdminSettings::getValueByKey(args[0])) {
            /* reprint the message */
            CommandsUtils::printSettingsPanel(this->bot, {this->query->message->chat->id, this->query->message->messageId}, this->settingsBoard); 
        }
    });
}

void BotCommands::join() {
    this->bot->getEvents().onCommand("join", [this](TgBot::Message::Ptr message) {
        if(!CommandsUtils::gameStarted) { return; }

        User::user user{message->from->username, message->from->id};

        if(!Database::existUser(&user, &Database::sqlErrs)) {
            if(Database::sqlErrs.error) {
                /* error */
                return;
            }
            if(!Database::insertUser(&user, &Database::sqlErrs)) {
                /* error */
                return;
            }
            
        }
    });     
}

void BotCommands::userMenu() {
    this->bot->getEvents().onCommand("myMenu", [this](TgBot::Message::Ptr message) {
        if(!CommandsUtils::gameStarted) {
            return;
        }
    });
}

void BotCommands::callBackQuery() {
    this->bot->getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        TgBot::ChatMember::Ptr user = this->bot->getApi().getChatMember(query->message->chat->id, query->from->id);
        this->query = query;

        if(CommandsUtils::idCreator != user->user->id) { return; }

        try {   
            if(query->data == "update_here") {
                if(CommandsUtils::settingsButtonClicked) { return; }

                CommandsUtils::settingsButtonClicked = true;
                CommandsUtils::printGeneralPanel(this->bot, query, user, this->generalBoard, false);
            }

            else if(query->data == "update_private") {
                if(CommandsUtils::settingsButtonClicked) { return; }

                CommandsUtils::settingsButtonClicked = true;
                CommandsUtils::printGeneralPanel(this->bot, query, user, this->generalBoard, true);
            }

            else if(query->data == "settings" && !CommandsUtils::gameStarted) {
                CommandsUtils::updateCommandAuth = true;
                CommandsUtils::printSettingsPanel(this->bot, {query->message->chat->id, query->message->messageId}, this->settingsBoard);
            }

            else if(query->data == "resetSettings" && !CommandsUtils::gameStarted) {
                CommandsUtils::lastCommand = "resetSettings";
                CommandsUtils::updateCommandAuth = false;

                CommandsUtils::printConfirmBoxReset(this->bot, query, this->confirmBoard);
            }

            else if(query->data == "deny") {
                if(CommandsUtils::lastCommand == "resetSettings" && !CommandsUtils::gameStarted) {
                    CommandsUtils::updateCommandAuth = true;

                    CommandsUtils::printSettingsPanel(this->bot, {query->message->chat->id, query->message->messageId}, this->settingsBoard);
                    return;
                }

                if(CommandsUtils::lastCommand == "start") {
                    this->bot->getApi().deleteMessage(query->message->chat->id, query->message->messageId);
                }
            }

            else if(query->data == "confirm") {
                if(CommandsUtils::lastCommand == "resetSettings" && !CommandsUtils::gameStarted) {
                    CommandsUtils::updateCommandAuth = false;

                    AdminSettings::clear();
                    AdminSettings::init();

                    CommandsUtils::editGeneralPanel(this->bot, query, user, this->generalBoard);
                    return;
                }

                if(CommandsUtils::lastCommand == "start") {
                    this->bot->getApi().deleteMessage(query->message->chat->id, query->message->messageId);

                    if(CommandsUtils::startBot(this->bot, query->message->chat->id, user)) {
                        CommandsUtils::printStartPanel(this->bot, query->message->chat->id, user, this->startKeyBoard);
                    }
                }
            }

            else if(query->data == "ToS") {
                CommandsUtils::printToS(this->bot, query, this->backToStartPanel);
            }
            
            else if(query->data == "copyrights") {
                CommandsUtils::printCopyRights(this->bot, query, this->backToStartPanel);
            }

            else if(query->data == "helpSettings" && !CommandsUtils::gameStarted) {
                CommandsUtils::updateCommandAuth = false;
                CommandsUtils::editSettingsPanel(this->bot, query, this->backToSettings);
            }

            else if(query->data == "backToStartPanel") {
                CommandsUtils::updateCommandAuth = false;
                CommandsUtils::editGeneralPanel(this->bot, query, user, this->generalBoard);
            }

            else if(query->data == "backToSettings") {
                CommandsUtils::updateCommandAuth = true;
                CommandsUtils::printSettingsPanel(this->bot, {query->message->chat->id, query->message->messageId}, this->settingsBoard);
            }

            else if(query->data == "startGame") {
                if(CommandsUtils::gameStarted) { return; }
                CommandsUtils::gameStarted = true; 

                CommandsUtils::printAdminJoin(this->bot, query, user);
            }
        }

        catch(std::exception& e) {
            return;
        }
    });
}
