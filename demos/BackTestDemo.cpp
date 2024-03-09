#include "../resources/BackTest.hpp"
#include "../resources/DataFrame.hpp"
#include "../resources/TradingStrategy.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>



int main() {
    DataFrame df("AAPL.csv");
    TradingStrategy ts(df);

    float bestSharpeRatio = -std::numeric_limits<float>::infinity();
    int bestSmallMA = -1;
    int bestLargeMA = -1;

    // Calculate the risk free rate for daily return calculations
    float riskFreeRate = .02f;
    float dailyRiskFreeRate = riskFreeRate / 252;

    for (int smallMA = 1; smallMA <= 200; smallMA += 10) {
        for (int largeMA = smallMA + 1; largeMA <= 200; largeMA += 10) {
            std::vector<std::string> signals = ts.movingAverageCrossover(smallMA, largeMA);
            BackTest bt(signals, df.getColumn("Close"), 10000.0f, 10);
            bt.run();
            float sharpeRatio = bt.getSharpeRatio(dailyRiskFreeRate);
            if (sharpeRatio > bestSharpeRatio) {
                bestSharpeRatio = sharpeRatio;
                bestSmallMA = smallMA;
                bestLargeMA = largeMA;
            }
        }
    }

    int vecSize = df.data.size();
    std::cout << "Size of the dataframe: " << vecSize << std::endl;
    std::cout << "Best Sharpe Ratio: " << bestSharpeRatio << std::endl;
    std::cout << "Best Small MA: " << bestSmallMA << std::endl;
    std::cout << "Best Large MA: " << bestLargeMA << std::endl;

    return 0;
}