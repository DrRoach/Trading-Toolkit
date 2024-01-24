#include "Account.h"

Account::Account()
{
    _DataFileName = "data.txt";
}

double Account::GetMaxRiskPercentage()
{
    return _MaxRisk * 100;
}

double Account::GetRiskPerTrade()
{
    return _TradingSize * _MaxRisk;
}

float Account::GetMaxRiskPerTrade()
{
    return _TradingSize * _MaxRisk;
}

float Account::GetLeverage()
{
    return _Leverage;
}

void Account::SetMaxRisk(float Risk)
{
    _MaxRisk = Risk / 100;
}

void Account::SetAccountSize(float Size)
{
    _Size = Size;
    SaveData();
}

void Account::SetTradingSize(float Size)
{
    _TradingSize = Size;
    SaveData();
}

void Account::Setup()
{
    if (IsSetup()) {
        LoadData();
    } else {
        GetData();
    }
}

int Account::ConsecutiveLosses()
{
    return (_Size - _TradingSize) / GetRiskPerTrade();
}

bool Account::IsSetup()
{
    std::ifstream DataFile (_DataFileName);
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

/**
 * Format for save file:
 *  AccountSize
 *  TradingSize
 *  Leverage
 */
void Account::SaveData()
{
    std::ofstream DataFile (_DataFileName);
    if (DataFile.is_open()) {
        DataFile << _Size << "\n";
        DataFile << _TradingSize << "\n";
        DataFile << _Leverage << "\n";
        DataFile.close();
    }
}

void Account::LoadData()
{
    std::ifstream DataFile (_DataFileName);
    if (DataFile.is_open()) {
        std::string line;
        int LineNum = 0;
        while (getline(DataFile, line)) {
            switch (LineNum++) {
                case 0:
                    _Size = std::stof(line);
                    break;
                case 1:
                    _TradingSize = std::stof(line);
                case 2:
                    _Leverage = std::stof(line);
                    break;
            }
        }
        DataFile.close();
    }
}

void Account::GetData()
{
    std::cout << "What is the account size?" << std::endl;
    std::cin >> _Size;

    std::cout << "What is the trading account size?" << std::endl;
    std::cin >> _TradingSize;

    std::cout << "What is the leverage?" << std::endl;
    std::cin >> _Leverage;

    SaveData();
}
