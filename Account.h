#include <fstream>
#include <string>
#include <iostream>

class Account
{
    public:
        Account();

        double GetMaxRiskPercentage();
        double GetRiskPerTrade();
        float GetMaxRiskPerTrade();
        float GetLeverage();

        void Setup();
        int ConsecutiveLosses();
        bool IsSetup();

    private:
        std::string _DataFileName;
        float _Size;
        float _TradingSize;
        static const double _MaxRisk = 0.01;
        float _Leverage;
        float _MaxRiskPerTrade;

        void SaveData();
        void LoadData();
        void GetData();
        void CalculateRequiredData();
};
