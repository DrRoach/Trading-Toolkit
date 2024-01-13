#include <string>
#include <iostream>
#include <fstream>

class Trade
{
    public:
        Trade(double OpenPrice, double Risk, float MaxRiskPerTrade, float Leverage);
        Trade(double OpenPrice, double Risk, double PositionSize, bool Active);

        double GetPositionSize();

        double CalculatePositionSize(double OpenPrice, double TradeRisk, float MaxRiskPerTrade, 
            float Leverage);

    private:
        double _Risk;
        double _OpenPrice;
        double _PositionSize;
        std::string _FileName;
        bool _Active = false;

        void Save();
};
