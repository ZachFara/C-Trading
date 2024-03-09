#include "BackTest.hpp"
#include <numeric>
#include <cmath>

BackTest::BackTest(std::vector<std::string> signals, std::vector<float> prices, float initialCapital, int sharesToBuy)
    : signals(signals), prices(prices), initialCapital(initialCapital), sharesToBuy(sharesToBuy), capital(initialCapital) {
    returns.reserve(signals.size());
}

void BackTest::run() {
    float previousCapital = initialCapital;
    for (int i = 0; i < signals.size(); i++) {
        if (signals[i] == "Buy" && capital >= prices[i] * sharesToBuy) {
            shares += sharesToBuy;
            capital -= prices[i] * sharesToBuy;
        } else if (signals[i] == "Sell" && shares >= sharesToBuy) {
            capital += sharesToBuy * prices[i];
            shares -= sharesToBuy;
        }
        float return_ = (capital - previousCapital) / previousCapital;
        returns.push_back(return_);
        previousCapital = capital;
    }
    // Sell remaining shares at the end
    if (shares > 0) {
        capital += shares * prices.back();
        shares = 0;
    }
}

float BackTest::getProfit() {
    return capital - initialCapital;
}

float BackTest::getReturn() {
    return (capital - initialCapital) / initialCapital;
}

float BackTest::getSharpeRatio(float riskFreeRate) {
    float avgReturn = std::accumulate(returns.begin(), returns.end(), 0.0f) / returns.size();
    float stdDev = std::sqrt(std::accumulate(returns.begin(), returns.end(), 0.0f, [avgReturn](float a, float b) { return a + std::pow(b - avgReturn, 2); }) / returns.size());
    return (avgReturn - riskFreeRate) / stdDev;
}