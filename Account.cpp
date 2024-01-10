#include "Account.h"

Account::Account()
{
    DataFileName = "data.txt";
}

double Account::GetMaxRiskPercentage()
{
    return MaxRisk * 100;
}

double Account::GetRiskPerTrade()
{
    return TradingSize * MaxRisk;
}

void Account::Setup()
{
    if (IsSetup()) {
        LoadData();
    } else {
        GetData();
    }
    CalculateRequiredData();
}

int Account::ConsecutiveLosses()
{
    return (Size - TradingSize) / GetRiskPerTrade();
}

bool Account::IsSetup()
{
    std::ifstream DataFile (DataFileName);
    int RequiredLines = 4;

    if (DataFile.is_open()) {
        std::string ignored;
        int NumOfLines = 0;
        while (getline(DataFile, ignored)) {
            NumOfLines++;
        }
        DataFile.close();
        return NumOfLines == RequiredLines;
    }
    return false;
}

double Account::CalculatePositionSize(double TradeRisk)
{
    double TradeRiskAsPercentage = TradeRisk / WholeTradeRisk;
    double RiskMultiplyer = 100 / (TradeRiskAsPercentage * 100);

    return MaxRiskPerTrade * RiskMultiplyer;
}

void Account::SaveData()
{
    std::ofstream DataFile (DataFileName);
    if (DataFile.is_open()) {
        DataFile << Size << "\n";
        DataFile << TradingSize << "\n";
        DataFile << TradeMaxRiskAsPercentage << "\n";
        DataFile << TradeMaxRiskAsPrice << "\n";
        DataFile.close();
    }
}

void Account::LoadData()
{
    std::ifstream DataFile (DataFileName);
    if (DataFile.is_open()) {
        std::string line;
        int LineNum = 0;
        while (getline(DataFile, line)) {
            switch (LineNum) {
                case 0:
                    Size = std::stof(line);
                    break;
                case 1:
                    TradingSize = std::stof(line);
                case 2:
                    TradeMaxRiskAsPercentage = std::stof(line);
                    break;
                case 3:
                    TradeMaxRiskAsPrice = std::stod(line);
                    break;
            }
            LineNum++;
        }
        DataFile.close();
    }
}

void Account::GetData()
{
    std::cout << "What is the account size?" << std::endl;
    std::cin >> Size;

    std::cout << "What is the trading account size?" << std::endl;
    std::cin >> TradingSize;

    std::cout << "What is the max risk per trade as a percentage?" << std::endl;
    std::cin >> TradeMaxRiskAsPercentage;

    std::cout << "What is the max risk per trade as price?" << std::endl;
    std::cin >> TradeMaxRiskAsPrice;

    SaveData();
}

void Account::CalculateRequiredData()
{
    MaxRiskPerTrade = TradingSize * MaxRisk;
    WholeTradeRisk = (100 / TradeMaxRiskAsPercentage) * TradeMaxRiskAsPrice;
}
