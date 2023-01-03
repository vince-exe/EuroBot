#include "bet.h"

Bet::Bet(int money, int state, std::string date) {
    this->money = money;
    this->state = state;
    this->date = date;
}

Bet::Bet(int id, int money, int state, std::string date) {
    this->id = id;
    this->money = money;
    this->state = state;
    this->date = date;
}

int Bet::getId() {
    return this->id;
}

void Bet::init(int money, int state, std::string date) {
    this->money = money;
    this->state = state;
    this->date = date;
}

int Bet::getMoney() {
    return this->money;
}

int Bet::getState() {
    return this->state;
}

std::string Bet::getDate() {
    return this->date;
}
