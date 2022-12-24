#include "database.h"

sql::Driver* Database::driver;

sql::Connection* Database::con;

sql::Statement* Database::stmt;

sql::ResultSet* Database::res;


bool DBUtils::startDatabase(const std::string hostname, const std::string user, const std::string password, const std::string schema) {
    DBErrors::SqlErrors sqlErrors;

    if(!Database::connect(hostname, user, password, schema, &sqlErrors)) {
        std::cout<<"\nError while attempting to connect..\n";

        std::cout<<"\n# ERR: " << sqlErrors.what;
        std::cout<<"\n# ERROR CODE: " << sqlErrors.errCode;
        std::cout<<"\n# SQL STATE: " << sqlErrors.sqlState;

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

        return false;
    }
}

void Database::destroy() {
    delete Database::con;
    delete Database::res;
    delete Database::stmt;
}

bool Database::existUser(const std::string id) {
    ;
}