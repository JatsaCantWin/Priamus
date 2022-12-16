//
// Created by peter on 11/21/22.
//

#ifndef PRIAMUS_COLUMN_H
#define PRIAMUS_COLUMN_H

#include <vector>
#include <string>

enum class DataType {Integer, FloatingPoint, String};

class Column {
private:
    DataType dataType;
    std::vector<std::string> dataContainer;
public:
    explicit Column(DataType dataType);
    void setCellDataAtIndex(int index, const std::string& data);
    std::string getCellDataAtIndex(int index);
    void appendCellData(const std::string& data);
    DataType getDataType();
    size_t getCellCount();
};


#endif //PRIAMUS_COLUMN_H
