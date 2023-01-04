#ifndef LOAN_H
#define LOAN_H

#include <string>


class Loan {
private:
    uint64_t donatorID;

    uint64_t receiverID;

    int coins;

    std::string date;

    int id;

    std::string receiverUsr;

public:
    Loan(uint64_t dID, uint64_t rID, int coins, std::string date);

    Loan(int id, int coins, std::string receiverUsr);

    uint64_t getDonatorID();

    uint64_t getRecevierID();

    int getCoins();

    int getId();

    std::string getRecUsr();
    
    std::string getDate();
};

#endif
