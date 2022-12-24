#include "database.h"

sql::Driver* Database::driver;

sql::Connection* Database::con;

sql::Statement* Database::stmt;

sql::ResultSet* Database::res;

sql::PreparedStatement* Database::pstmt;

DBErrors::SqlErrors Database::sqlErrs;

bool DBUtils::startDatabase(const std::string hostname, const std::string user, const std::string password, const std::string schema) {
    if(!Database::connect(hostname, user, password, schema, &Database::sqlErrs)) {
        std::cout<<"\nError while attempting to connect..\n";

        std::cout<<"\n# ERR: " << Database::sqlErrs.what;
        std::cout<<"\n# ERROR CODE: " << Database::sqlErrs.errCode;
        std::cout<<"\n# SQL STATE: " << Database::sqlErrs.sqlState;

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

bool Database::existUser(User::user* user, DBErrors::SqlErrors* sqlErr) {
    try {
        sqlErr->error = false;
        Database::pstmt = Database::con->prepareStatement(
            "SELECT ID FROM users WHERE users.ID = ?;"
        );  
        Database::pstmt->setString(1, std::to_string(user->id));
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

bool Database::insertUser(User::user* user, DBErrors::SqlErrors* sqlErr) {
    try {
        sqlErr->error = false;
        Database::pstmt = Database::con->prepareStatement(
            "INSERT INTO users (ID, username) VALUES (?, ?);"
        );
        Database::pstmt->setString(1, std::to_string(user->id));
        Database::pstmt->setString(2, user->username);

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