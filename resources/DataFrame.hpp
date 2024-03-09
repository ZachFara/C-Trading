#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;


class DataFrame{
public:
    // Attributes
    vector<string> columnNames;
    vector<vector<float>> data;
    vector<string> dates;

    // Methods
    DataFrame(string fileName);
    vector<float> getColumn(string columnName);
    vector<float> getRow(int rowIndex);
    void show(int nRows = 5);
    vector<float> sliceRow(int rowIndex, int start, int end);
    vector<float> sliceColumn(string columnName, int start, int end);
private:
    string fileName;
    int dateColumnIndex;
};

#endif