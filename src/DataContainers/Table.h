//
// Created by peter on 11/9/22.
//

#ifndef PRIAMUS_TABLE_H
#define PRIAMUS_TABLE_H

#include <map>
#include <string>
#include "Column.h"

class Table {
private:
    std::map<std::string, Column> dataContainer;
public:
    Column& getColumnByName(const std::string& columnName);
    Column& getColumnByIndex(int index);
    std::string getColumnNameByIndex(int index);
    size_t getColumnCount();
    size_t getRowCount();
    void deleteColumnByName(const std::string& columnName);
    void insertColumn(const std::string& columnName, const Column& column);
    void print();
};


#endif //PRIAMUS_TABLE_H
