#!/bin/bash
clear
g++ EuroBot.cpp loan/loan.cpp bet/bet.cpp user/user.cpp database/database.cpp utils/utils.cpp utils/JsonReader/json_reader.cpp utils/CommandsUtils/commands_utils.cpp utils/AdminSettings/admin_settings.cpp commands/bot_commands.cpp -o telegram_bot --std=c++14 -I/usr/local/include -I/usr/include/cppconn -L/usr/lib -lmysqlcppconn -lTgBot -lboost_system -lssl -lcrypto -lpthread
./telegram_bot