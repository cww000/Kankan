#include <iostream>
#include <cstring>
#include <mariadb/conncpp.hpp>

// Print all records in tasks table 
void showTasks(std::unique_ptr<sql::Connection> &conn) {
    try {
    	std::cout << "xiaosowo" << std::endl;
        // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from user;");
        // Loop through and print results
        while (res->next()) {
            std::cout << "id = " << res->getInt(1);
            std::cout << ", key = " << res->getString(2);
            std::cout << ", nickname = " << res->getString(3) << "\n";
        }
    }
    catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }
}

// Main Process
int main(int argc, char **argv){
    if (argc==1){
        std::cout << "Please provide an argument.\n";
    }
    else {
        try {
            // Instantiate Driver
            sql::Driver* driver = sql::mariadb::get_driver_instance();

            // Configure Connection
            sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/Kankan");
            sql::Properties properties({{"user", "zc"}, {"password", "20010202"}});

            // Establish Connection
            std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

            // Use arguments to determine execution next steps
            if (!strcmp(argv[1],"showTasks")) {
            	std::cout << "1" << std::endl;
                showTasks(conn);
            }

            // Close Connection
            conn->close();
        }
        catch(sql::SQLException& e){
            std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
            // Exit (Failed)
            return 1;
        }
    }

    // Exit (Success)
    return 0;
}
