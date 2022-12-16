//
// Created by peter on 11/21/22.
//

#include <iostream>
#include "Column.h"

Column::Column(DataType dataType) {
    this->dataType = dataType;
}

void Column::setCellDataAtIndex(int index, const std::string& data) {
    dataContainer[index] = data;
}

std::string Column::getCellDataAtIndex(int index) {
    return dataContainer[index];
}

void Column::appendCellData(const std::string& data) {
    dataContainer.push_back(data);
}

DataType Column::getDataType() {
    return dataType;
}

size_t Column::getCellCount() {
    return dataContainer.size();
}


