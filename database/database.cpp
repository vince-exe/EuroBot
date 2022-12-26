#include "database.h"

sql::Driver* Database::driver;

sql::Connection* Database::con;

sql::Statement* Database::stmt;

sql::ResultSet* Database::res;

sql::PreparedStatement* Database::pstmt;

bool DBUtils::startDatabase(const std::string hostname, const std::string user, const std::string password, const std::string schema) {
    DBErrors::SqlErrors sqlErr;

    if(!Database::connect(hostname, user, password, schema, &sqlErr)) {
        std::cout<<"\nError while attempting to connect..\n";

        std::cout<<"\n# ERR: " << sqlErr.what;
        std::cout<<"\n# ERROR CODE: " << sqlErr.errCode;
        std::cout<<"\n# SQL STATE: " <<sqlErr.sqlState;

        return false;
    }

    std::cout<<"\nSuccessfully connected to the database!!";
    
    return true;
}

bool Database::connect(const std::string hostName, const std::string user, const std::string password, const std::string schema, DBErrors::SqlErrors* sqlErr) {
    try {
        /* create a connection */
        Database::driver = get_driver_instance();
        Database::con = Database::driver->connect(hostName, user, password);
        
        /* connect to the schema */
        Database::con->setSchema(schema);
        Database::stmt = Database::con->createStatement();

        return true;
    } 
    catch(sql::SQLException &e) {
        sqlErr->what = e.what();
        sqlErr->errCode = e.getErrorCode();
        sqlErr->sqlState = e.getSQLState();
        sqlErr->error = true;

        return false;
    }
}

void Database::destroy() {
    delete Database::con;
    delete Database::res;
    delete Database::stmt;
}

bool Database::existUser(User* user, DBErrors::SqlErrors* sqlErr) {
    try {
        sqlErr->error = false;
        Database::pstmt = Database::con->prepareStatement(
            "SELECT ID FROM users WHERE users.ID = ?;"
        );  
        Database::pstmt->setString(1, std::to_string(user->getId()));
        Database::res = Database::pstmt->executeQuery();

        return (Database::res->rowsCount()) ? true : false;
    }
    catch(sql::SQLException &e) {
        sqlErr->what = e.what();
        sqlErr->errCode = e.getErrorCode();
        sqlErr->sqlState = e.getSQLState();
        sqlErr->error = true;
    }  
}

bool Database::insertUser(User* user, DBErrors::SqlErrors* sqlErr) {
    try {
        sqlErr->error = false;
        Database::pstmt = Database::con->prepareStatement(
            "INSERT INTO users (ID, username, coins) VALUES (?, ?, ?);"
        );
        Database::pstmt->setString(1, std::to_string(user->getId()));
        Database::pstmt->setString(2, user->getUsername());
        Database::pstmt->setInt(3, user->getCoins());

        Database::pstmt->executeUpdate();

        return true;
    }
    catch(sql::SQLException &e) {
        sqlErr->what = e.what();
        sqlErr->errCode = e.getErrorCode();
        sqlErr->sqlState = e.getSQLState();
        sqlErr->error = true;

        return false;
    }
}

User Database::getUser(int64_t id, DBErrors::SqlErrors* sqlErr) {
    try {
        sqlErr->error = false;
        Database::pstmt = Database::con->prepareStatement(
            "SELECT * FROM users WHERE users.ID = ?;"
        );
        Database::pstmt->setString(1, std::to_string(id));
        Database::res = Database::pstmt->executeQuery();

        if(res->next()) {
            return User(strtoll(res->getString("ID").c_str(), NULL, 0), res->getString("username"), res->getInt(3));
        }
        return User();
    }
    catch(sql::SQLException &e) {
        sqlErr->what = e.what();
        sqlErr->errCode = e.getErrorCode();
        sqlErr->sqlState = e.getSQLState();

        sqlErr->error = true;
        return User();
    }
}