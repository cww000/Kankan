#include <iostream>
#include <cstring>
#include <mariadb/conncpp.hpp>

// Create a new task record
void addTask(std::unique_ptr<sql::Connection> &conn, std::string description) {
    try {
        // Create a new PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into use  values (1,2,'哈哈哈')"));

        // Bind values to SQL statement
       // stmnt->setString(1, description);
        // Execute query
        stmnt->executeQuery();
    }
    catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

// Print all records in tasks table 
void showTasks(std::unique_ptr<sql::Connection> &conn) {
    try {
        // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from user;");
        // Loop through and print results
        while (res->next()) {
            std::wcout << "id = " << res->getInt(1);
            std::wcout << ", key = " << res->getString(2);
            //std::cout << ", type = " << res->getType();
            std::wcout << ", nickname = " << res->getString(3) 
            //std::cout << ", type = " << res->getType() 
	    << "\n";
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
                showTasks(conn);
            } else if (!strcmp(argv[1],"addTask")) {
                if (argc != 3) {
                    std::cout << "Invalid arguments";
                    return 1;
                }
                addTask(conn, argv[2]);
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
