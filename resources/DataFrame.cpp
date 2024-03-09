// DataFrame.cpp
#include "DataFrame.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>


DataFrame::DataFrame(std::string fileName){
    this->fileName = fileName;

    // Open the file
    std::ifstream file(fileName);

    if (!file.is_open()){
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(1);
    }

    // Read the header row
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string columnName;
    int dateColumnIndex = -1;
    int index = 0;
    while (std::getline(ss, columnName, ',')) {
        columnNames.push_back(columnName);
        if (columnName == "Date") {
            dateColumnIndex = index;
        }
        index++;
    }

    // Check if date column was found
    if (dateColumnIndex == -1) {
        std::cerr << "Error: Date column not found" << std::endl;
        exit(1);
    }

    // Read the data
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string cell;
        std::vector<float> oneRow;
        index = 0;
        while (std::getline(ss, cell, ',')) {
            if (index == dateColumnIndex) {
                dates.push_back(cell);
            } else {
                oneRow.push_back(std::stof(cell));
            }
            index++;
        }
        data.push_back(oneRow);
    }
}

void DataFrame::show(int nRows){
    // Print the first nRows of the data
    for (int i = 0; i < nRows; i++){
        std::cout << "Date: " << dates[i] << " ";
        for (int j = 0; j < columnNames.size(); j++){
            if (columnNames[j] == "Date") {
                continue;
            }
            std::cout << columnNames[j] << ": " << data[i][j - (dateColumnIndex < j ? 1 : 0)] << " ";
        }
        std::cout << std::endl;
    }
}

vector<float> DataFrame::getColumn(string columnName){
    // Return the column with the name columnName
    for (int i = 0; i < columnNames.size(); i++){
        if (columnNames[i] == columnName){
            vector<float> column;
            for (int j = 0; j < data.size(); j++){
                column.push_back(data[j][i]);
            }
            return column;
        }
    }
    std::cerr << "Error: Column not found" << std::endl;
    exit(1);
}


vector<float> DataFrame::getRow(int rowIndex){
    // Return the row with the index rowIndex
    if (rowIndex < data.size()){
        return data[rowIndex];
    }
    std::cerr << "Error: Row not found" << std::endl;
    exit(1);
}

vector<float> DataFrame::sliceRow(int rowIndex, int start, int end) {
    start = std::max(0, start);
    end = std::min((int)data[rowIndex].size(), end);
    return vector<float>(data[rowIndex].begin() + start, data[rowIndex].begin() + end);
}

vector<float> DataFrame::sliceColumn(string columnName, int start, int end) {
    int columnIndex = find(columnNames.begin(), columnNames.end(), columnName) - columnNames.begin();
    vector<float> columnData;
    for (int i = 0; i < data.size(); i++) {
        columnData.push_back(data[i][columnIndex]);
    }
    start = std::max(0, start);
    end = std::min((int)columnData.size(), end);
    return vector<float>(columnData.begin() + start, columnData.begin() + end);
}
