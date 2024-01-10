#include <fstream>
#include <string>
#include <iostream>

class Account
{
    public:
        Account();

        double GetMaxRiskPercentage();
        double GetRiskPerTrade();

        void Setup();
        int ConsecutiveLosses();
        bool IsSetup();
        double CalculatePositionSize(double TradeRisk);

    private:
        std::string DataFileName;
        float Size;
        float TradingSize;
        static const double MaxRisk = 0.01;
        float TradeMaxRiskAsPercentage;
        double TradeMaxRiskAsPrice;
        float MaxRiskPerTrade;
        double WholeTradeRisk;

        void SaveData();
        void LoadData();
        void GetData();
        void CalculateRequiredData();
};
