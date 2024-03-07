#include "DataFrame.hpp"
#include <vector>
#include <string>

class TradingStrategy {
public:
    TradingStrategy(DataFrame df);
    std::vector<std::string> movingAverageCrossover(int fastPeriod, int slowPeriod);

private:
    DataFrame df;
    std::vector<float> getMovingAverage(int period);
};