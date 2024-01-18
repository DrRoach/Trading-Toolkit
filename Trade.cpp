#include "Trade.h"

Trade::Trade(double OpenPrice, double Risk, float MaxRiskPerTrade, float Leverage)
{
    std::cout << "Trade con" << std::endl << OpenPrice << " " << Risk << " " << MaxRiskPerTrade << " " << Leverage << std::endl;
    _OpenPrice = OpenPrice;
    _Risk = Risk;
    _PositionSize = CalculatePositionSizeInMoney(_OpenPrice, _Risk, MaxRiskPerTrade, Leverage);
    _FileName = "trades/" + std::to_string(_OpenPrice) + "-" + std::to_string(_Risk);

    Save();
}

Trade::Trade(double OpenPrice, double Risk, double PositionSize, bool Active, bool Ended)
{
    _OpenPrice = OpenPrice;
    _Risk = Risk;
    _PositionSize = PositionSize;
    _Active = Active;
    _Ended = Ended;

    _FileName = "trades/" + std::to_string(_OpenPrice) + "-" + std::to_string(_Risk);
}

double Trade::GetPositionSize()
{
    return _PositionSize;
}

double Trade::GetOpenPrice()
{
    return _OpenPrice;
}

double Trade::GetRisk()
{
    return _Risk;
}

bool Trade::IsActive()
{
    return _Active;
}

void Trade::PrintInfo(int ID, float Leverage)
{
    std::cout << "ID: " << ID << " Open price: " << GetOpenPrice() << " Risk: " << GetRisk() << 
        " Position size in money: " << GetPositionSize() << " Position size in units: " << 
        CalculatePositionSizeInUnits(GetPositionSize(), Leverage) << " Active: " << IsActive() << 
        std::endl;
}

double Trade::CalculatePositionSizeInMoney(double OpenPrice, double TradeRisk, float MaxRiskPerTrade, 
    float Leverage)
{
    return MaxRiskPerTrade * (1 / (TradeRisk / (OpenPrice / Leverage)));
}

int Trade::CalculatePositionSizeInUnits(double PositionSizeInMoney, float Leverage)
{
    return PositionSizeInMoney * Leverage;
}

void Trade::Activate()
{
    _Active = true;
    Save();
}

void Trade::Delete()
{
    // Delete the trade file
    std::remove(_FileName.c_str());
}

void Trade::End()
{
    _Ended = true;
    Save();
}

/**
 * Format for trade file:
 *  OpenPrice
 *  Risk
 *  PositionSize
 *  Active
 *  Ended
 */
void Trade::Save()
{
    std::ofstream TradeFile (_FileName);
    if (TradeFile.is_open()) {
        TradeFile << _OpenPrice << "\n";
        TradeFile << _Risk << "\n";
        TradeFile << _PositionSize << "\n";
        TradeFile << _Active << "\n";
        TradeFile << _Ended << "\n";
        TradeFile.close();
    }
}
