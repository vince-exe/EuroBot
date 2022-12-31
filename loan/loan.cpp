#include "loan.h"

Loan::Loan(uint64_t dID, uint64_t rID, int coins, std::string date) {
    this->donatorID = dID;
    this->receiverID = rID;
    this->coins = coins;
    this->date = date;
}

int Loan::getCoins() {
    return this->coins;
}

std::string Loan::getDate() {
    return this->date;
}

uint64_t Loan::getDonatorID() {
    return this->donatorID;
}

uint64_t Loan::getRecevierID() {
    return this->receiverID;
}