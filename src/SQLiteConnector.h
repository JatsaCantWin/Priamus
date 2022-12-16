#ifndef PRIAMUS_SQLITECONNECTOR_H
#define PRIAMUS_SQLITECONNECTOR_H

#include <sqlite3.h>
#include <string>
#include "DataContainers/Table.h"
#include "DataContainers/Column.h"

class SQLiteConnector {
private:
    sqlite3 *databasePointer{};
public:
    explicit SQLiteConnector(const std::string& databasePath);
    ~SQLiteConnector();

    Table constructTable(const std::string& tableName);
    int executeSQL(const std::string& sqlStatement, Table& returnTable);
};


#endif //PRIAMUS_SQLITECONNECTOR_H
