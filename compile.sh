#!/bin/bash
clear
g++ EuroBot.cpp utils/utils.cpp utils/JsonReader/json_reader.cpp commands/bot_commands.cpp -o telegram_bot --std=c++14 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread
./telegram_bot