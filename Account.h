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

        void SetMaxRisk(float Risk);
        void SetAccountSize(float Size);
        void SetTradingSize(float Size);

        void Setup();
        int ConsecutiveLosses();
        bool IsSetup();

    private:
        std::string _DataFileName;
        float _Size;
        float _TradingSize;
        double _MaxRisk = 0.01;
        float _Leverage;

        void SaveData();
        void LoadData();
        void GetData();
};
