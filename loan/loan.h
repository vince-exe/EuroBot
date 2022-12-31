#ifndef LOAN_H
#define LOAN_H

#include <string>


class Loan {
private:
    uint64_t donatorID;

    uint64_t receiverID;

    int coins;

    std::string date;

public:
    Loan(uint64_t dID, uint64_t rID, int coins, std::string date);

    uint64_t getDonatorID();

    uint64_t getRecevierID();

    int getCoins();

    std::string getDate();
};

#endif
