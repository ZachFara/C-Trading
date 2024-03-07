// DataFrame.cpp
#include "DataFrame.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

DataFrame::DataFrame(std::string fileName){
    this->fileName = fileName;

    // Open the file
    std::ifstream file(fileName);

    if (!file.is_open()){
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(1);
    }

    // Read the column names
    std::string line;
    std::getline(file, line);
    std::string oneColumnName = "";
    for (char c : line){
        if (c == ','){
            columnNames.push_back(oneColumnName);
            oneColumnName = "";
        }
        else{
            oneColumnName += c;
        }
    }
    // Add the last column name
    if (!oneColumnName.empty()) {
        columnNames.push_back(oneColumnName);
    }

    // Read the data
    std::vector<float> oneRow;
    while (std::getline(file, line)){
        std::string oneNumber = "";
        for (char c : line){
            if (c == ','){
                oneRow.push_back(std::stof(oneNumber));
                oneNumber = "";
            }
            else{
                oneNumber += c;
            }
        }
        // Add the last number in the row
        if (!oneNumber.empty()) {
            oneRow.push_back(std::stof(oneNumber));
        }
        // Add the row to the data
        data.push_back(oneRow);
        // Clear the oneRow vector for the next row
        oneRow.clear();
    }

}

void DataFrame::show(int nRows){
    // Print the first nRows of the data
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < columnNames.size(); j++){
            std::cout << columnNames[j] << ": " << data[i][j] << " ";
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
