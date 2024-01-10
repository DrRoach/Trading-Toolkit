#include "Input.h"
#include "Account.h"

Input::Input(Account* account)
{
    _Account = account;

    std::string Command;

    while (Command != "q") {
        std::cout << "Enter command. ? for help." << std::endl;
        std::cin >> Command;

        if (Command == "?") {
            Help();
        } else if (Command == "psc") {
            PositionSizeCalculator();
        }
    }
}

void Input::Help()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "psc - Position size calculator. Work out position size for trade" << std::endl;
    std::cout << "? - List available commands" << std::endl;
    std::cout << "q - Quit program" << std::endl;
}

void Input::PositionSizeCalculator()
{
    double TradeRisk;

    std::cout << "What is the trade risk?" << std::endl;
    std::cin >> TradeRisk;

    // Work out 1% of TradingAccountSize relative to TradeRisk. If TradeRisk is 5% then 
    //  5% of PositionSize needs to be MaxRiskPerTrade
    
    printf("Position size: %.2f\n", _Account->CalculatePositionSize(TradeRisk));
}
