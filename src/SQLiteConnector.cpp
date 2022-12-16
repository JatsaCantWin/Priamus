#include <iostream>
#include <regex>
#include "SQLiteConnector.h"

SQLiteConnector::SQLiteConnector(const std::string& databasePath) {
    sqlite3_open(databasePath.c_str(), &databasePointer);
}

SQLiteConnector::~SQLiteConnector() {
    sqlite3_close(databasePointer);
}

int SQLiteConnector::executeSQL(const std::string& sqlStatement, Table &returnTable) {
    auto sqlCallback = [](void *returnTable, int columnCount, char** fieldContent, char** columnNames) -> int    // * Constructs return string containing the tables that were operated on
    {
        for (int i = 0; i < columnCount; i++)
        {
            (*(Table*)returnTable).insertColumn(columnNames[i], Column(DataType::String));
            (*(Table*)returnTable).getColumnByName(columnNames[i]).appendCellData(fieldContent[i] ? std::string(fieldContent[i]) : std::string("NULL"));
            std::cout << (*(Table*)returnTable).getColumnCount() << " " << (*(Table*)returnTable).getRowCount() << std::endl;
        }
        return 0;
    };

    sqlite3_exec(databasePointer, sqlStatement.c_str(), sqlCallback, &returnTable, nullptr);

    return 0;
}

Table SQLiteConnector::constructTable(const std::string& tableName) {
    Table returnTable;
    std::vector<DataType> dataTypes;

    Table tableInfo;
    std::string tableInfoSql;
    tableInfoSql.append("PRAGMA TABLE_INFO(").append(tableName).append(")");
    executeSQL(tableInfoSql, tableInfo);
    for (int i = 0; i<tableInfo.getRowCount(); i++)
    {
        if (std::regex_match(tableInfo.getColumnByName("type").getCellDataAtIndex(i), std::regex("NVARCHAR(.*)")))
            dataTypes.push_back(DataType::String);
        else if (std::regex_match(tableInfo.getColumnByName("type").getCellDataAtIndex(i), std::regex("NUMERIC(.*)")))
            dataTypes.push_back(DataType::FloatingPoint);
        else if (std::regex_match(tableInfo.getColumnByName("type").getCellDataAtIndex(i), std::regex("INTEGER")))
            dataTypes.push_back(DataType::Integer);
    }
    Table tableData;
    std::string tableDataSql;
    tableDataSql.append("SELECT * FROM ").append(tableName);
    executeSQL(tableInfoSql, tableInfo);
    for (int i = 0; i < tableData.getColumnCount(); i++)
    {
        returnTable.insertColumn(tableData.getColumnNameByIndex(i), Column(dataTypes[i]));
        Column& currentColumn = returnTable.getColumnByName(tableData.getColumnNameByIndex(i));
        for(int j = 0; j < tableData.getRowCount(); j++)
        {
            currentColumn.appendCellData(tableData.getColumnByIndex(i).getCellDataAtIndex(j));
        }
    }

    return returnTable;
}
