#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

#include "../bet/bet.h"

class User {
private:
    std::string username;

    int64_t id;

    int coins;

    Bet bet;

public:
    User();
    
    User(int64_t id, std::string username, int coins);

    std::string getUsername();

    int64_t getId();

    int getCoins();

    Bet getBet();

    void addCoins(int coins);

    void remCoins(int coins);

    void setBet(int money, int state, std::string date);
};

class UserManager {
private:
    static std::vector<int64_t> idVec;

public:
    static bool exist(int64_t id);

    static void push(int64_t id);
};

#endif
