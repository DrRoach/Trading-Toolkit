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
    int RequiredLines = 3;

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

double Account::CalculatePositionSize(double OpenPrice, double TradeRisk)
{
    // Work out move required for every £1 staked
    double LeverageMultiplyer = OpenPrice / Leverage;

    double TradeRiskAsPercentage = TradeRisk / LeverageMultiplyer;
    double RiskMultiplyer = 1 / TradeRiskAsPercentage;

    return MaxRiskPerTrade * RiskMultiplyer;
}

/**
 * Format for save file:
 *  AccountSize
 *  TradingSize
 *  MaxRiskAsPercentage (This will be replaced with leverage)
 *  MaxRiskAsPrice (This will be replaced with leverage)
 */
void Account::SaveData()
{
    std::ofstream DataFile (DataFileName);
    if (DataFile.is_open()) {
        DataFile << Size << "\n";
        DataFile << TradingSize << "\n";
        DataFile << Leverage << "\n";
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
                    Leverage = std::stof(line);
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

    std::cout << "What is the leverage?" << std::endl;
    std::cin >> Leverage;

    SaveData();
}

void Account::CalculateRequiredData()
{
    MaxRiskPerTrade = TradingSize * MaxRisk;
}
