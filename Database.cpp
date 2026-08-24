#include "../HeaderCode/Database.h"
#include <iostream>
#include <mysqlx/xdevapi.h>
#include <iomanip>
using namespace std;

Database::Database()
    : host("localhost"), 
    user("root"), 
    password("root"), 
    database("coffee_shop"), 
    port(33060) {
        Connect();
}

Database::~Database() {
    Disconnect();
}

void Database::Connect() {
    if(!session){
        try {
        session = make_unique<mysqlx::Session>(host, port, user, password, database);
        cout << "Connected to the database successfully." << endl;
        cout << "Host: " << host << endl;
        cout << "Port: " << port << endl;
        cout << "Database: " << database << endl;
        cout << "Press any key to continue..." << endl;
        cin.get();
        cin.clear();
        system("cls");
        } catch (const mysqlx::Error& err) {
            cerr << "Error connecting to the database: " << err.what() << endl;
        } catch (const std::exception& ex) {
            cerr << "Standard exception: " << ex.what() << endl;
        } catch (...) {
            cerr << "Unknown error occurred while connecting to the database." << endl;
        }
    }
}

void Database::Disconnect() {
    if (session) {
        session->close();
        cout << "Disconnected from the database." << endl;
    }
}

bool Database::AdminAuth(string& username, string& password){
    if(!session){
        cout << "Database not connected" << endl;
        return false;
    }
    try{
        mysqlx::SqlResult adminauth = session->sql(
        "select AdminID "
        "from admins "
        "where Username = ? "
        "and PasswordHash = ? "
        "and AdminStatus = 'Active'"
        )
        .bind(username, password)
        .execute();

        mysqlx::Row row = adminauth.fetchOne();

        return static_cast<bool>(row);
    }
    catch(const mysqlx::Error& error){
        cerr << error.what() << endl;
        return false;
    }
}

void Database::viewAdmin(){
        mysqlx::SqlResult admins = session->sql(
        "SELECT "
        "AdminID, "
        "Username, "
        "AdminName, "
        "AdminStatus, "
        "DATE_FORMAT(CreatedAt, '%Y-%m-%d %H:%i:%s') AS CreatedAt "
        "FROM ADMINS "
        "ORDER BY AdminID"
        )
        .execute();

        vector<mysqlx::Row> row = admins.fetchAll();

        cout << "====================================================================================\n";
        cout << "| "
            << left << setw(4)  << "ID"
            << "| " << setw(14) << "Username"
            << "| " << setw(25) << "Role"
            << "| " << setw(10) << "Status"
            << "| " << setw(20) << "Timestamp"
            << "|\n";
        cout << "====================================================================================\n";
        for (const mysqlx::Row& currentRow : row)
        {
            cout << "| "
                << left << setw(4)  << currentRow[0]
                << "| " << setw(14) << currentRow[1]
                << "| " << setw(25) << currentRow[2]
                << "| " << setw(10) << currentRow[3]
                << "| " << setw(20) << currentRow[4]
                << "|\n";
        }
        cout << "====================================================================================\n";
}

void Database::updateAdmin(int choice, string username, string change){
    switch(choice){
        case 1:
        try{
            session->sql(
            "UPDATE ADMINS "
            "SET USERNAME = ? "
            "WHERE USERNAME = ? "
        )
        .bind(username, change)
        .execute();
        }catch (const mysqlx::Error& error){
            cerr << error.what() << endl;
        }

        case 2:
        try{
            session->sql(
            "UPDATE ADMINS "
            "SET PASSWORDHASH = ? "
            "WHERE USERNAME = ? "
        )
        .bind(username, change)
        .execute();
        }catch (const mysqlx::Error& error){
            cerr << error.what() << endl;
        }

        case 3:
        try{
            session->sql(
            "UPDATE ADMINS "
            "SET ADMINNAME = ? "
            "WHERE USERNAME = ? "
        )
        .bind(username, change)
        .execute();
        }catch (const mysqlx::Error& error){
            cerr << error.what() << endl;
        }

        case 4:
        try{
            session->sql(
            "UPDATE ADMINS "
            "SET ADMINSTATUS = ? "
            "WHERE USERNAME = ? "
        )
        .bind(username, change)
        .execute();
        }catch (const mysqlx::Error& error){
            cerr << error.what() << endl;
        }
    }
}

void Database::createAdmin(string username, string pw, string adminname){
    try{
        session->sql(
        "INSERT INTO "
        "ADMINS (USERNAME, PASSWORDHASH, ADMINNAME) "
        "VALUES (?, ?, ?)"
    )
    .bind(username, pw, adminname)
    .execute();
    }catch (const mysqlx::Error& error){
        cerr << error.what() << endl;
    }
}

void Database::deleteAdmin(string username)
{
    try{
        mysqlx::SqlResult result = session->sql(
            "DELETE FROM ADMINS "
            "WHERE USERNAME = ?"
        )
        .bind(username)
        .execute();

        if (result.getAffectedItemsCount() == 0)
        {
            std::cout << "Category was not found.\n";
        }

        std::cout << "Category deleted successfully.\n";
    }catch (const mysqlx::Error& error){
        std::cerr
            << "Failed to delete category: "
            << error.what()
            << '\n';
    }
}

double Database::getBeveragePrice(string BeverageName){
    try{
        mysqlx::SqlResult result = session->sql(
            "SELECT CAST(BASEPRICE AS DOUBLE) " 
            "FROM BEVERAGES "
            "WHERE BEVERAGENAME = ? "
            "AND BEVERAGESTATUS = 'AVAILABLE'"
        )
        .bind(BeverageName)
        .execute();

        mysqlx::Row row = result.fetchOne();
        if (!row) {
            std::cerr << "Add-on not found: " << BeverageName << '\n';
            return 0.0;
        }
        return row[0].get<double>();
    }catch (const mysqlx::Error& error){
        std::cerr
            << "Failed to find: "
            << error.what()
            << '\n';
            return 0;
    }
}

double Database::getSizePrice(string SizeName){
    try{
        mysqlx::SqlResult result = session->sql(
            "SELECT CAST(ADDITIONALPRICE AS DOUBLE) " 
            "FROM SIZE_OPTIONS "
            "WHERE SIZENAME = ? "
            "AND SIZESTATUS = 'ACTIVE' "
        )
        .bind(SizeName)
        .execute();

        mysqlx::Row row = result.fetchOne();
        if (!row) {
            std::cerr << "Add-on not found: " << SizeName << '\n';
            return 0.0;
        }
        return row[0].get<double>();
    }catch (const mysqlx::Error& error){
        std::cerr
            << "Failed to find: "
            << error.what()
            << '\n';
            return 0;
    }
}

double Database::getAddOnPrice(string AddOnName){
    if(AddOnName != "None"){
        try{
        mysqlx::SqlResult result = session->sql(
            "SELECT CAST(ADDONPRICE AS DOUBLE) " 
            "FROM ADD_ONS "
            "WHERE ADDONNAME = ? "
            "AND ADDONSTATUS = 'ACTIVE' "
        )
        .bind(AddOnName)
        .execute();

        mysqlx::Row row = result.fetchOne();
        if (!row) {
            std::cerr << "Add-on not found: " << AddOnName << '\n';
            return 0.00;
        }
        return row[0].get<double>();
        }catch (const mysqlx::Error& error){
            std::cerr
                << "Failed to find: "
                << error.what()
                << '\n';
                return 0.00;
        }
    }

    return 0.00;
}