#include "TradingStrategy.hpp"

TradingStrategy::TradingStrategy(DataFrame df) : df(df) {}

std::vector<std::string> TradingStrategy::movingAverageCrossover(int fastPeriod, int slowPeriod) {
    std::vector<float> fastMA = getMovingAverage(fastPeriod);
    std::vector<float> slowMA = getMovingAverage(slowPeriod);

    std::vector<std::string> signals(fastMA.size(), "Hold");
    for (int i = 1; i < fastMA.size(); i++) {
        if (fastMA[i] > slowMA[i] && fastMA[i-1] < slowMA[i-1]) {
            signals[i] = "Buy";
        } else if (fastMA[i] < slowMA[i] && fastMA[i-1] > slowMA[i-1]) {
            signals[i] = "Sell";
        } else {
            signals[i] = "Hold";
        }
    }

    return signals;
}

std::vector<float> TradingStrategy::getMovingAverage(int period) {
    std::vector<float> prices = df.getColumn("Close");
    std::vector<float> movingAverage(prices.size());

    for (int i = period - 1; i < prices.size(); i++) {
        float sum = 0;
        for (int j = 0; j < period; j++) {
            sum += prices[i - j];
        }
        movingAverage[i] = sum / period;
    }

    return movingAverage;
}