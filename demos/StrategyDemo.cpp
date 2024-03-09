#include "../resources/DataFrame.hpp"
#include "../resources/TradingStrategy.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() {

    DataFrame df("AAPL.csv");

    TradingStrategy ts(df);

    std::vector<std::string> signals = ts.movingAverageCrossover(50, 200);

    // Print out the signals along with the corresponding dates
    std::vector<std::string> dates = df.dates;

    std::cout << "Length of dates: " << dates.size() << std::endl;
    std::cout << "Length of signals: " << signals.size() << std::endl;

    #include <map>

    // Count the occurrences of each signal
    std::map<std::string, int> signalCounts;
    for (const std::string& signal : signals) {
        signalCounts[signal]++;
    }

    // Print the value counts
    for (const auto& pair : signalCounts) {
        std::cout << "Signal: " << pair.first << ", Count: " << pair.second << std::endl;
    }

    return 0;
}