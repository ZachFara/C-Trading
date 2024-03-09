#include <vector>
#include <string>

class BackTest {
    std::vector<std::string> signals;
    std::vector<float> prices;
    float initialCapital;
    int sharesToBuy;
    float shares = 0;
    float capital = 0;
    std::vector<float> returns;

public:
    BackTest(std::vector<std::string> signals, std::vector<float> prices, float initialCapital, int sharesToBuy);

    void run();

    float getProfit();

    float getReturn();

    float getSharpeRatio(float riskFreeRate);
};