#include "loan.h"

Loan::Loan(uint64_t dID, uint64_t rID, int coins, std::string date) {
    this->donatorID = dID;
    this->receiverID = rID;
    this->coins = coins;
    this->date = date;
}

Loan::Loan(int id, int coins, std::string receiverUsr) {
    this->id = id;
    this->coins = coins;
    this->receiverUsr = receiverUsr;
}

int Loan::getCoins() {
    return this->coins;
}

int Loan::getId() {
    return this->id;
}

std::string Loan::getRecUsr() {
    return this->receiverUsr;
}

std::string Loan::getDate()  {
    return this->date;
}

uint64_t Loan::getDonatorID() {
    return this->donatorID;
}

uint64_t Loan::getRecevierID() {
    return this->receiverID;
}