#include "user.h"
 
User::User() {
    this->id = 0;
}

User::User(int64_t id, std::string username, int coins) {
    this->id = id;
    this->username = username;
    this->coins = coins;
}

std::string User::getUsername() {
    return this->username;
}

int User::getCoins() {
    return this->coins;
}

int64_t User::getId() {
    return this->id;
}

Bet User::getBet() {
    return this->bet;   
}

void User::addCoins(int coins) {
    this->coins += coins;
}

void User::remCoins(int coins) {
    this->coins -= coins;
}

void User::setBet(int money, int state, std::string date) {
    this->bet.init(money, state, date);
}

std::vector<int64_t> UserManager::idVec;

bool UserManager::exist(int64_t id) {
    for(auto& id_ : UserManager::idVec) {
        if(id_ == id) { return true; }
    }

    return false;
}

void UserManager::push(int64_t id) {
    UserManager::idVec.push_back(id);
}

void UserManager::clear() {
    UserManager::idVec.clear();
}
