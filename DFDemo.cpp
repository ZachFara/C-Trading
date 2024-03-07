#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "resources/DataFrame.hpp"
using std::string;
using std::vector;


int main() {

    system("python3 download_data.py");

    DataFrame df("AAPL.csv");

    std::cout << "The first 5 rows of the DataFrame are: " << std::endl;
    df.show();

    vector<float> close = df.getColumn("Close");
    vector<float> rowTwo = df.getRow(2);
    
    std::cout << "The first 5 elements of the close vector are: " << std::endl;
    for (int i = 0; i < 5; i++){
        std::cout << close[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "The first 3 elements of the rowTwo vector are: " << std::endl;
    for (int i = 0; i < 3; i++){
        std::cout << rowTwo[i] << " ";
    }
    std::cout << std::endl;

    // Demonstrate that we can use the .data attribute to access the data
    std::cout << "A couple of points in the data attribute are: " << std::endl;
    std::cout << df.data[0][0] << " " << df.data[0][1] << std::endl;


    // Demonstrate that we can use the sliceRow method
    vector<float> slicedRow = df.sliceRow(0, 1, 4);
    std::cout << "The first 3 elements of the slicedRow vector are: " << std::endl;
    for (int i = 0; i < 3; i++){
        std::cout << slicedRow[i] << " ";
    }

    // Demonstrate that we can use the sliceColumn method
    vector<float> slicedColumn = df.sliceColumn("Close", 1, 4);
    std::cout << "The first 3 elements of the slicedColumn vector are: " << std::endl;
    for (int i = 0; i < 3; i++){
        std::cout << slicedColumn[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}