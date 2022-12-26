#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>


class User {
private:
    std::string username;

    int64_t id;

    int coins;

public:
    User();
    
    User(int64_t id, std::string username, int coins);

    std::string getUsername();

    int64_t getId();

    int getCoins();

    void addCoins(int coins);

    void remCoins(int coins);
};

class UserManager {
private:
    static std::vector<int64_t> idVec;

public:
    static bool exist(int64_t id);

    static void push(int64_t id);
};

#endif
