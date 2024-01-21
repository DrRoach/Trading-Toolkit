#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

class Trade
{
    public:
        Trade(double OpenPrice, double Risk, float MaxRiskPerTrade, float Leverage);
        Trade(double OpenPrice, double Risk, double PositionSize, bool Active, bool Ended, 
            double ClosePrice);

        double GetPositionSize();
        double GetOpenPrice();
        double GetRisk();
        bool IsActive();

        void PrintInfo(int ID, float Leverage);

        double CalculatePositionSizeInMoney(double OpenPrice, double TradeRisk, float MaxRiskPerTrade, 
            float Leverage);
        int CalculatePositionSizeInUnits(double PositionSizeInMoney, float Leverage);
        double CalculateRisk(double OpenPrice, double PositionSize, double Risk, float Leverage);

        void Activate();
        void Delete();
        void End(double ClosePrice);

    private:
        double _Risk;
        double _OpenPrice;
        double _ClosePrice;
        double _ProfitOrLoss;
        double _PositionSize;
        std::string _FileName;
        bool _Active = false;
        bool _Ended = false;

        void Save();
};
