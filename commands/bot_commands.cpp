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

    Utils::setKeyBoard((this->settingsBoard), 
    {
        {"⚙️ Ripristina", "resetSettings"},
        {"✅ Salva", "saveSettings"}
    }
    );
    Utils::setKeyBoard((this->settingsBoard),
    {
        {"🔙 Back", "backToStartPanel"},
        {"🆘 Help", "helpSettings"}
    }
    );

    Utils::setKeyBoard((this->backToSettings), {{"🔙 Back", "backToSettings"}});

    this->start();
    this->update();
    this->callBackQuery();
}

void BotCommands::start() {
    this->eventBroadCaster->onCommand("start", [this](TgBot::Message::Ptr message) {
        TgBot::ChatMember::Ptr user = this->bot->getApi().getChatMember(message->chat->id, message->from->id);
        
        /* if it's a private channel */
        if(message->chat->id == user->user->id) { 
            CommandsUtils::printStartPrivatePanel(this->bot, message, user);
            return;
        }

        std::string groupIdStr = JsonReader::getJsonObj()["groupId"];
        long long grouId = strtoll(groupIdStr.c_str(), NULL, 0);  

        if(grouId != message->chat->id) { return; }

        if(user->status != "creator") { return; }

        Utils::idCreator = user->user->id;

        CommandsUtils::printStartPanel(this->bot, message, user, this->startKeyBoard);
    });
}

void BotCommands::update() {
    this->eventBroadCaster->onCommand("update", [this](TgBot::Message::Ptr message) {
        if(!Utils::updateCommandAuth || message->from->id != Utils::idCreator) { return; }

        if(CommandsUtils::countArguments("/update", message->text) != 2) { return; }

        std::vector<std::string> args = CommandsUtils::getArguments("/update", message->text);
        if(AdminSettings::exist(args[0])) { std::cout<<"\nesiste"; }
    });
}

void BotCommands::callBackQuery() {
    this->bot->getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        TgBot::ChatMember::Ptr user = this->bot->getApi().getChatMember(query->message->chat->id, query->from->id);
        
        if(Utils::idCreator != user->user->id) { return; }
        
        try {
            if(query->data == "update_here") {
                CommandsUtils::printGeneralPanel(this->bot, query, user, this->generalBoard, false);
            }

            else if(query->data == "update_private") {
                CommandsUtils::printGeneralPanel(this->bot, query, user, this->generalBoard, true);
            }

            else if(query->data == "startGame") {
                ;
            }

            else if(query->data == "settings") {
                Utils::updateCommandAuth = true;
                CommandsUtils::printSettingsPanel(this->bot, query, this->settingsBoard);
            }

            else if(query->data == "ToS") {
                CommandsUtils::printToS(this->bot, query, this->backToStartPanel);
            }
            
            else if(query->data == "copyrights") {
                CommandsUtils::printCopyRights(this->bot, query, this->backToStartPanel);
            }

            else if(query->data == "helpSettings") {
                Utils::updateCommandAuth = false;
                CommandsUtils::editSettingsPanel(this->bot, query, this->backToSettings);
            }

            else if(query->data == "backToStartPanel") {
                Utils::updateCommandAuth = false;
                CommandsUtils::editGeneralPanel(this->bot, query, user, this->generalBoard);
            }

            else if(query->data == "backToSettings") {
                Utils::updateCommandAuth = true;
                CommandsUtils::printSettingsPanel(this->bot, query, this->settingsBoard);
            }
        }

        catch(std::exception& e) {
            return;
        }
    });
}
