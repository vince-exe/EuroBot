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


namespace DBErrors {
    struct SqlErrors {
        std::string what;
        int errCode;
        std::string sqlState;
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

    static bool existUser(const std::string id);
};

#endif
