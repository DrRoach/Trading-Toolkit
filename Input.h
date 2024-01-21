#include <string>
#include <iostream>
#include <vector>
#include <dirent.h>
class Account;
class Trade;

class Input
{
    public:
        Input();

    private:
        Account* _Account;
        std::vector<Trade*> _Trades;

        std::vector<Trade*> GetActiveTrades();

        void LoadTrades();
        void Help();
        void Quit();
        void PositionSizeCalculator();
        void PrepTrade();
        void ListTrades();
        void ListActiveTrades();
        void CancelTrade();
        void ActivateTrade();
        void EndTrade();
        void SetRisk();
        void RiskCalculator();
};
