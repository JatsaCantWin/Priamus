#include <iostream>
#include <iomanip>
#include "Table.h"

Column& Table::getColumnByName(const std::string& columnName) {
    return dataContainer.find(columnName)->second;
}

void Table::deleteColumnByName(const std::string& columnName) {
    dataContainer.erase(columnName);
}

Column& Table::getColumnByIndex(int index)
{
    auto returnColumn = dataContainer.begin();
    std::advance(returnColumn, index);
    return returnColumn->second;
}

std::string Table::getColumnNameByIndex(int index)
{
    auto returnColumn = dataContainer.begin();
    std::advance(returnColumn, index);
    return returnColumn->first;
}

size_t Table::getColumnCount() {
    return dataContainer.size();
}

size_t Table::getRowCount() {
    return dataContainer.begin()->second.getCellCount();
}

void Table::insertColumn(const std::string& columnName, const Column& column) {
    if (dataContainer.find(columnName) != dataContainer.end())  // ? if column already exists, don't insert it
        return;
    dataContainer.insert({columnName, column});
}

void Table::print() {
    for (unsigned long int i = 0; i < getColumnCount(); i++)
    {
        std::cout << std::setw(30) << getColumnNameByIndex(i) << " | " ;
    }
    std::cout << std::endl;
    for (unsigned long int j = 0; j < getRowCount(); j++) {
        for (unsigned long int i = 0; i < getColumnCount(); i++) {
            std::cout << std::setw(30) << getColumnByIndex(i).getCellDataAtIndex(j) << " | ";
        }
        std::cout << std::endl;
    }
}
