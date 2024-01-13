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

        void LoadTrades();
        void Help();
        void Quit();
        void PositionSizeCalculator();
        void PrepTrade();
        void ListTrades();
};
