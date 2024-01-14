#include "Input.h"
#include "Account.h"
#include "Trade.h"

Input::Input()
{
    _Account = new Account();
    _Account->Setup();

    LoadTrades();

    std::cout << "Trade risk is set to " << _Account->GetMaxRiskPercentage() << "%" << std::endl;
    std::cout << "Max risk per trade is: " << _Account->GetRiskPerTrade() << std::endl;

    std::cout << "You can lose " << _Account->ConsecutiveLosses() << " trades in a row" << 
        std::endl;

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
        } else if (Command == "lt") {
            ListTrades();
        }
    }
}

void Input::LoadTrades()
{
    // Load all of the saved trades
    DIR *dr;
    struct dirent *en;
    dr = opendir("./trades");
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if (strcmp(en->d_name, ".") == 0 || strcmp(en->d_name, "..") == 0) {
                continue;
            }
            // Load the trade data from the file
            std::string TradeDataFileName = "trades/" + std::string(en->d_name);
            std::ifstream TradeDataFile (TradeDataFileName);
            if (TradeDataFile.is_open()) {
                double OpenPrice;
                double Risk;
                double PositionSize;
                bool Active;
                int LineNum = 0;
                std::string line;
                while (getline(TradeDataFile, line)) {
                    switch (LineNum++) {
                        case 0:
                            OpenPrice = std::stod(line);
                            break;
                        case 1:
                            Risk = std::stod(line);
                            break;
                        case 2:
                            PositionSize = std::stod(line);
                            break;
                        case 4:
                            Active = line == "0";
                            break;
                    }
                }
                _Trades.emplace_back(new Trade(OpenPrice, Risk, PositionSize, Active));
            }
        }
        closedir(dr);
    } else {
        std::cout << "Couldn't open" << std::endl;
    }
}

void Input::Help()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "psc - Position size calculator. Work out position size for trade" << std::endl;
    std::cout << "pt - Prep trade. Prepare for an upcoming trade. Can be marked active or cancelled later." 
        << std::endl;
    std::cout << "lt - List trades. List all of the prepped and active trades." << std::endl;
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

    Trade* trade;
    printf("Position size: %.2f\n", trade->CalculatePositionSize(
        OpenPrice, TradeRisk, _Account->GetMaxRiskPerTrade(), _Account->GetLeverage()));
}

void Input::PrepTrade()
{
    double OpenPrice;
    double TradeRisk;

    std::cout << "What is the trade open price?" << std::endl;
    std::cin >> OpenPrice;

    std::cout << "What is the trade risk?" << std::endl;
    std::cin >> TradeRisk;

    Trade* trade = new Trade(OpenPrice, TradeRisk, 
        _Account->GetMaxRiskPerTrade(), _Account->GetLeverage());
    _Trades.emplace_back(trade);

    printf("Position size: %.2f\n", trade->GetPositionSize());
    delete trade;
}

void Input::ListTrades()
{
    std::cout << "Number of trades: " << _Trades.size() << std::endl;
    for (int i = 0; i < _Trades.size(); i++) {
        Trade* trade = _Trades.at(i);
        std::cout << "ID: " << i << " Open price: " << trade->GetOpenPrice() << " Risk: " << 
            trade->GetRisk() << " Position size: " << trade-> GetPositionSize() << std::endl;
    }
}
