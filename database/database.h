#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <stdlib.h>
#include <vector>

#include <mysql-cppconn-8/jdbc/cppconn/driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/connection.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/resultset.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
#include <mysql-cppconn-8/jdbc/mysql_connection.h>

#include "../user/user.h"
#include "../bet/bet.h"
#include "../loan/loan.h"

namespace DBErrors {
    struct SqlErrors {
        std::string what;

        int errCode;

        std::string sqlState;

        bool error;
    };
}


namespace DBUtils {
    /**
     * @brief start the database and fetch the errors 
     * 
     * @param hostname the hostname
     * 
     * @param user the user
     * 
     * @param password the password for the user
     *  
     * @param schema database's schema where the queries will be done 
     */
    bool startDatabase(const std::string hostname, const std::string user, const std::string password, const std::string schema);
}


class Database {
private:
    static sql::Driver *driver;

    static sql::Connection *con;

    static sql::Statement *stmt;

    static sql::ResultSet *res;

    static sql::PreparedStatement *pstmt;

public:
    /**
     * @brief connect to the hostname using user and password
     *
     * @param hostName the hostname
     * 
     * @param user the SQL user
     *  
     * @param password the password for the user
     * 
     * @return true if a connection is established else false
     */
    static bool connect(const std::string hostName, const std::string user, const std::string password, const std::string schema, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief free all the allocated sql objects
     * 
     * @warning possible segmentation fault if this method is invoked and the objects doesn't have been allocated
     * 
     */
    static void destroy();

    /**
     * @brief checks if a user exist in the database
     * 
     * @param id user identifier for the exist condition
     * 
     * @param sqlErr a pointer to struct used when an error is present
     * 
     * @return true if the user is in the database
     * 
     * @return false if the user isn't in the database
     */
    static bool existUser(User* user, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief insert a user in the database
     * 
     * @param user the user to insert
     * 
     * @param sqlErr a pointer to struct used when an error is present
     * 
     * @return true if the insertion went fine
     * 
     * @return false if the insertion went not fine
     */
    static bool insertUser(User* user, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief insert a bet in the database
     * 
     * @param userId the user unique identifier
     * 
     * @param bet the bet object
     * 
     * @param sqlErr a pointer to struct used when an error is present
     * 
     * @return true if the insertion went fine
     * 
     * @return false if the insertion went not fine
     */
    static bool insertBet(int64_t userId, Bet bet, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief return a User istance
     * 
     * @param id the unique identifier of the user
     * 
     * @param sqlErr a pointer to struct used when an error is present
     * 
     * @return User istance
     */
    static User getUser(int64_t id, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief return a User istance
     * 
     * @param username the username of the user
     * 
     * @param sqlEerr a pointer to struct used when an error is present
     * 
     * @return User istance
     */
    static User getUser(const std::string& username, DBErrors::SqlErrors* sqlErr);
    
    /**
     * @brief insert a loan in the database
     *  
     * @param loan the loan to insert
     *  
     * @param sqlErr a pointer to struct used when an error is present
     * 
     */
    static bool insertLoan(Loan& loan, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief get a vector of bets in the given date
     * 
     * @param userID user unique identifier
     * 
     * @param date date of the bets
     *  
     * @param sqlErr a pointer to struct used when an error is present
     */
    static std::vector<Bet> getBets(int64_t userID, const std::string& date, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief get a vector filled with the user's username
     * 
     * @param sqlErr a pointer to struct used when an error is present
     * 
     */
    static std::vector<std::string> getUsersList(DBErrors::SqlErrors* sqlErr);

    /**
     * @brief update a the 'coins' paramater of the user
     * 
     * @param id the user unique identifier
     * 
     * @param sqlErr a pointer to struct used when an error is present
     * 
     * @param User a pointer to a user istance 
     * 
     * @return true if the update went fine
     *  
     * @return false if the update went not fine 
     */
    static bool updateUserCoins(DBErrors::SqlErrors* sqlErr, User* user);
};

#endif
