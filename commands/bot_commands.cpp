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

    Utils::setKeyBoard((this->generalBoard),
    {
        {"© Sviluppatori", "copyrights"},
        {"📖 Termini & Condizioni", "ToS"}
    }
    );
    Utils::setKeyBoard((this->generalBoard), {{"🔧 Impostazioni", "settings"}});

    Utils::setKeyBoard((this->backToStartPanel), {{"🔙 Back", "backToStartPanel"}});

    Utils::setKeyBoard((this->settingsBoard), {{"⚙️ Ripristina", "resetSettings"}});

    Utils::setKeyBoard((this->settingsBoard),
    {
        {"🔙 Back", "backToStartPanel"},
        {"🆘 Help", "helpSettings"}
    }
    );

    Utils::setKeyBoard((this->backToSettings), {{"🔙 Back", "backToSettings"}});

    Utils::setKeyBoard((this->confirmBoard), 
    {
        {"❌ Annulla", "deny"},
        {"✅ Conferma", "confirm"}
    }
    );

    this->start();
    this->update();
    this->callBackQuery();
}

void BotCommands::start() {
    this->eventBroadCaster->onCommand("start", [this](TgBot::Message::Ptr message) {
        TgBot::ChatMember::Ptr user = this->bot->getApi().getChatMember(message->chat->id, message->from->id);
        CommandsUtils::lastCommand = "start";

        if(CommandsUtils::startCommand) {
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
            CommandsUtils::printSettingsPanel(this->bot, this->query, this->settingsBoard); 
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

            else if(query->data == "startGame") {
                ;
            }

            else if(query->data == "settings") {
                CommandsUtils::updateCommandAuth = true;
                CommandsUtils::printSettingsPanel(this->bot, query, this->settingsBoard);
            }

            else if(query->data == "resetSettings") {
                CommandsUtils::lastCommand = "resetSettings";
                CommandsUtils::updateCommandAuth = false;

                CommandsUtils::printConfirmBoxReset(this->bot, query, this->confirmBoard);
            }

            else if(query->data == "deny") {
                if(CommandsUtils::lastCommand == "resetSettings") {
                    CommandsUtils::updateCommandAuth = true;

                    CommandsUtils::printSettingsPanel(this->bot, query, this->settingsBoard);
                    return;
                }

                if(CommandsUtils::lastCommand == "start") {
                    this->bot->getApi().deleteMessage(query->message->chat->id, query->message->messageId);
                }
            }

            else if(query->data == "confirm") {
                if(CommandsUtils::lastCommand == "resetSettings") {
                    CommandsUtils::updateCommandAuth = false;

                    AdminSettings::clear();
                    AdminSettings::init();

                    CommandsUtils::editGeneralPanel(this->bot, query, user, this->generalBoard);
                    return;
                }

                if(CommandsUtils::lastCommand == "start") {
                    this->bot->getApi().deleteMessage(query->message->chat->id, query->message->messageId);

                    CommandsUtils::startBot(this->bot, query->message->chat->id, user);
                    CommandsUtils::printStartPanel(this->bot, query->message->chat->id, user, this->startKeyBoard);
                }
            }

            else if(query->data == "ToS") {
                CommandsUtils::printToS(this->bot, query, this->backToStartPanel);
            }
            
            else if(query->data == "copyrights") {
                CommandsUtils::printCopyRights(this->bot, query, this->backToStartPanel);
            }

            else if(query->data == "helpSettings") {
                CommandsUtils::updateCommandAuth = false;
                CommandsUtils::editSettingsPanel(this->bot, query, this->backToSettings);
            }

            else if(query->data == "backToStartPanel") {
                CommandsUtils::updateCommandAuth = false;
                CommandsUtils::editGeneralPanel(this->bot, query, user, this->generalBoard);
            }

            else if(query->data == "backToSettings") {
                CommandsUtils::updateCommandAuth = true;
                CommandsUtils::printSettingsPanel(this->bot, query, this->settingsBoard);
            }
        }

        catch(std::exception& e) {
            return;
        }
    });
}
