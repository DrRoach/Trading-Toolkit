#include "Input.h"
#include "Account.h"
#include "Trade.h"

Input::Input()
{
    _Account = new Account();
    _Account->Setup();

    std::cout << "Trade risk is set to " << _Account->GetMaxRiskPercentage() << "%" << std::endl;
    std::cout << "Max risk per trade is: " << _Account->GetRiskPerTrade() << std::endl;

    std::cout << "You can lose " << _Account->ConsecutiveLosses() << " trades in a row" << std::endl;

    std::string Command;

    while (Command != "q") {
        std::cout << "Enter command. ? for help." << std::endl;
        std::cin >> Command;

        if (Command == "?") {
            Help();
        } else if (Command == "psc") {
            PositionSizeCalculator();
        } else if (Command == "pt") {
            PrepTrade();
        }
    }
}

void Input::Help()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "psc - Position size calculator. Work out position size for trade" << std::endl;
    std::cout << "pt - Prep trade. Prepare for an upcoming trade. Can be marked active or cancelled later." << std::endl;
    std::cout << "? - List available commands" << std::endl;
    std::cout << "q - Quit program" << std::endl;
}

void Input::PositionSizeCalculator()
{
    double TradeRisk;
    double OpenPrice;

    std::cout << "What is the open price?" << std::endl;
    std::cin >> OpenPrice;

    std::cout << "What is the trade risk?" << std::endl;
    std::cin >> TradeRisk;

    // Work out how far price will have to move for p/l to change by 1p

    // Work out 1% of TradingAccountSize relative to TradeRisk. If TradeRisk is 5% then 
    //  5% of PositionSize needs to be MaxRiskPerTrade
    
    printf("Position size: %.2f\n", _Account->CalculatePositionSize(OpenPrice, TradeRisk));
}

void Input::PrepTrade()
{
    double OpenPrice;
    double TradeRisk;

    std::cout << "What is the trade open price?" << std::endl;
    std::cin >> OpenPrice;

    std::cout << "What is the trade risk?" << std::endl;
    std::cin >> TradeRisk;

    Trades.emplace_back(new Trade(TradeRisk, OpenPrice));
}
