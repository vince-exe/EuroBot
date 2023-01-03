#ifndef BET_H
#define BET_H

#include <string>
#include <iostream>


class Bet {
private:
    int money;

    int state;

    int id;

    std::string date;

public:
    Bet() = default;

    Bet(int money, int state, std::string date);

    Bet(int id, int money, int state, std::string date);

    void init(int money, int state, std::string date);

    int getMoney();

    int getState();

    int getId();
    
    std::string getDate();

};

#endif