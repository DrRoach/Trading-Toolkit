#include <string>
#include <iostream>
#include <vector>
class Account;
class Trade;

class Input
{
    public:
        Input();
    private:
        Account* _Account;
        std::vector<Trade*> Trades;

        void Help();
        void Quit();
        void PositionSizeCalculator();
        void PrepTrade();
};
