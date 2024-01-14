#include "Trade.h"

Trade::Trade(double OpenPrice, double Risk, float MaxRiskPerTrade, float Leverage)
{
    _OpenPrice = OpenPrice;
    _Risk = Risk;
    _PositionSize = CalculatePositionSize(_OpenPrice, _Risk, MaxRiskPerTrade, Leverage);
    _FileName = "trades/" + std::to_string(_OpenPrice) + "-" + std::to_string(_Risk);

    Save();
}

Trade::Trade(double OpenPrice, double Risk, double PositionSize, bool Active)
{
    _OpenPrice = OpenPrice;
    _Risk = Risk;
    _PositionSize = PositionSize;
    _Active = Active;
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

double Trade::CalculatePositionSize(double OpenPrice, double TradeRisk, float MaxRiskPerTrade, 
    float Leverage)
{
    return MaxRiskPerTrade * (1 / (TradeRisk / (OpenPrice / Leverage)));
}

/**
 * Format for trade file:
 *  OpenPrice
 *  Risk
 *  PositionSize
 *  Active
 */
void Trade::Save()
{
    std::ofstream TradeFile (_FileName);
    if (TradeFile.is_open()) {
        TradeFile << _OpenPrice << "\n";
        TradeFile << _Risk << "\n";
        TradeFile << _PositionSize << "\n";
        TradeFile << _Active << "\n";
        TradeFile.close();
    }
}
