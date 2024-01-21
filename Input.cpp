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
        } else if (Command == "ct") {
            CancelTrade();
        } else if (Command == "at") {
            ActivateTrade();
        } else if (Command == "et") {
            EndTrade();
        } else if (Command == "sr") {
            SetRisk();
        } else if (Command == "rc") {
            RiskCalculator();
        } else if (Command == "q") {
            // This is here so we don't enter "Unknown command" else
        } else {
            std::cout << "Unknown command." << std::endl;
            Help();
        }
    }
}

std::vector<Trade*> Input::GetActiveTrades()
{
    std::vector<Trade*> ActiveTrades;

    for (int i = 0; i < _Trades.size(); i++) {
        Trade* trade = _Trades.at(i);
        if (!trade->IsActive()) {
            continue;
        }

        ActiveTrades.emplace_back(_Trades.at(i));
    }

    return ActiveTrades;
}

void Input::LoadTrades()
{
    // Clear out all trades
    _Trades.erase(_Trades.begin(), _Trades.end());

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
                bool Ended;
                double ClosePrice;
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
                        case 3:
                            Active = line == "1";
                            break;
                        case 4:
                            Ended = line == "1";
                            break;
                        case 5:
                            ClosePrice = std::stod(line);
                            break;
                    }
                }
                _Trades.emplace_back(new Trade(OpenPrice, Risk, PositionSize, Active, Ended, 
                    ClosePrice));
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
    std::cout << "pt - Prep trade. Prepare for an upcoming trade. Can be marked active or cancelled later" 
        << std::endl;
    std::cout << "lt - List trades. List all of the prepped and active trades" << std::endl;
    std::cout << "ct - Cancel trade. Cancel a prepped trade and delete its related data" << 
        std::endl;
    std::cout << "at - Activate trade. Activate a prepped trade" << std::endl;
    std::cout << "et - End trade. End an active trade" << std::endl;
    std::cout << "sr - Set risk. Set the maximum risk per trade as a percentage. WARNING - Risking more than 1% of your account can end badly." << std::endl;
    std::cout << "rc - Risk calculator. Use open price and position size to work out how much will be lost on a losing trade." << std::endl;
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

    double PositionSizeInMoney = trade->CalculatePositionSizeInMoney(OpenPrice, TradeRisk, 
        _Account->GetMaxRiskPerTrade(), _Account->GetLeverage());

    printf("Position size in money: %.2f\n", PositionSizeInMoney);
    std::cout << "Position size in units: " << trade->CalculatePositionSizeInUnits(
        PositionSizeInMoney, _Account->GetLeverage()) << std::endl;
}

void Input::PrepTrade()
{
    double OpenPrice;
    double TradeRisk;

    std::cout << "What is the trade open price?" << std::endl;
    std::cin >> OpenPrice;

    std::cout << "What is the trade risk?" << std::endl;
    std::cin >> TradeRisk;

    Trade* trade = new Trade(OpenPrice, TradeRisk, _Account->GetMaxRiskPerTrade(), 
        _Account->GetLeverage());
    _Trades.push_back(trade);

    printf("Position size in money: %.2f\n", trade->GetPositionSize());
    std::cout << "Position size in units: " << trade->CalculatePositionSizeInUnits(
        trade->GetPositionSize(), _Account->GetLeverage()) << std::endl;
}

void Input::ListTrades()
{
    std::cout << "Number of trades: " << _Trades.size() << std::endl;
    for (int i = 0; i < _Trades.size(); i++) {
        Trade* trade = _Trades.at(i);
        trade->PrintInfo(i, _Account->GetLeverage());
    }
}

void Input::ListActiveTrades()
{
    std::vector<Trade*> ActiveTrades = GetActiveTrades();

    std::cout << "Number of active trades: " << ActiveTrades.size() << std::endl;

    for (int i = 0; i < ActiveTrades.size(); i++) {
        Trade* trade = ActiveTrades.at(i);
        trade->PrintInfo(i, _Account->GetLeverage());
    }
}

void Input::CancelTrade()
{
    int TradeID;

    ListTrades();
    std::cout << "Which trade would you like to cancel?" << std::endl;
    std::cin >> TradeID;

    Trade* trade = _Trades.at(TradeID);
    trade->Delete();

    _Trades.erase(_Trades.begin() + TradeID);
}

void Input::ActivateTrade()
{
    if (_Trades.size() == 0) {
        std::cout << "No prepped trades exist." << std::endl;
        return;
    }

    int TradeID;

    ListTrades();
    std::cout << "Which trade would you like to activate?" << std::endl;
    std::cin >> TradeID;

    if (TradeID >= _Trades.size()) {
        std::cout << "Invalid trade ID" << std::endl;
        return;
    }

    Trade* trade = _Trades.at(TradeID);
    trade->Activate();

    _Trades.at(TradeID) = trade;
}

void Input::EndTrade()
{
    if (_Trades.size() == 0) {
        std::cout << "No active trades exist." << std::endl;
        return;
    }

    int TradeID;

    ListActiveTrades();

    std::cout << "Which trade would you like to end?" << std::endl;
    std::cin >> TradeID;

    std::vector<Trade*> ActiveTrades = GetActiveTrades();

    if (TradeID >= ActiveTrades.size()) {
        std::cout << "Invalid trade ID" << std::endl;
        return;
    }

    double ClosePrice;

    std::cout << "What was the close price?" << std::endl;
    std::cin >> ClosePrice;

    Trade* trade = ActiveTrades.at(TradeID);
    trade->End(ClosePrice);

    LoadTrades();
}

void Input::SetRisk()
{
    float Risk;

    std::cout << "What risk would you like to set (as a percentage)?" << std::endl;

    std::cin >> Risk;

    _Account->SetMaxRisk(Risk);
}

void Input::RiskCalculator()
{
    double Risk;
    double PositionSize;
    double OpenPrice;

    std::cout << "What is the open price?" << std::endl;
    std::cin >> OpenPrice;

    std::cout << "What is the position size?" << std::endl;
    std::cin >> PositionSize;

    std::cout << "What is the risk?" << std::endl;
    std::cin >> Risk;

    Trade* trade;
    std::cout << "Potential loss is: " << trade->CalculateRisk(OpenPrice, PositionSize, Risk,
        _Account->GetLeverage()) << std::endl;
}
