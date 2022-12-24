#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <stdlib.h>

#include <mysql-cppconn-8/jdbc/cppconn/driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/connection.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/resultset.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
#include <mysql-cppconn-8/jdbc/mysql_connection.h>

#include "../user/user.h"

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
     * @brief property of type DBErrors::SqlErrors used to check if an error occurred
     * 
     */
    static DBErrors::SqlErrors sqlErrs;
    
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
     * @param sqlErr a struct used when an error is present
     * 
     * @return true if the user is in the database
     * 
     * @return false if the user isn't in the database
     */
    static bool existUser(User::user* user, DBErrors::SqlErrors* sqlErr);

    /**
     * @brief insert a user in the database
     * 
     * @param user the user to insert
     * 
     * @param sqlErr a struct used when an error is present
     * 
     * @return true if the insertion went fine
     * 
     * @return false if the insertion went not fine
     */
    static bool insertUser(User::user* user, DBErrors::SqlErrors* sqlErr);
};

#endif
