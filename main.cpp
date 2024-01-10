#include <iostream>
#include <fstream>
#include <string>

int main()
{
    float AccountSize;
    float TradingAccountSize;
    float MaxRisk = 0.01;
    float MaxRiskAsPercentage;
    double MaxRiskAsPrice;
    float RiskReward;
    double MaxRiskPerTrade;


    std::ifstream DataFile ("data.txt");
    bool FileExists = false;
    if (DataFile.is_open()) {
        std::string line;
        int LineNum = 0;
        while (getline(DataFile, line)) {
            FileExists = true;
            switch (LineNum) {
                case 0:
                    AccountSize = std::stof(line);
                    break;
                case 1:
                    TradingAccountSize = std::stof(line);
                case 2:
                    MaxRiskAsPercentage = std::stof(line);
                    break;
                case 3:
                    MaxRiskAsPrice = std::stod(line);
                    break;
            }
            LineNum++;
        }
        DataFile.close();
    }

    if (!FileExists) {
        // Get data and write it to file
        std::cout << "What is the account size?" << std::endl;
        std::cin >> AccountSize;
        std::cout << "What is the trading account size?" << std::endl;
        std::cin >> TradingAccountSize;
        std::cout << "What is the max risk per trade as a percentage?" << std::endl;
        std::cin >> MaxRiskAsPercentage;
        std::cout << "What is the max risk per trade as price?" << std::endl;
        std::cin >> MaxRiskAsPrice;

        std::ofstream InDataFile ("data.txt");
        if (InDataFile.is_open()) {
            InDataFile << AccountSize << "\n";
            InDataFile << TradingAccountSize << "\n";
            InDataFile << MaxRiskAsPercentage << "\n";
            InDataFile << MaxRiskAsPrice << "\n";
            InDataFile.close();
        }
    }

    std::cout << "Trade max risk is set to 1%" << std::endl;
    MaxRiskPerTrade = TradingAccountSize * MaxRisk;
    std::cout << "Max risk per trade is: " << MaxRiskPerTrade << std::endl;

    std::cout << "You can lose " << (AccountSize - TradingAccountSize) / MaxRiskPerTrade << " trades in a row" << std::endl;
    

    double WholeTradeRisk = (100 / MaxRiskAsPercentage) * MaxRiskAsPrice;

    double TradeRisk;

    std::cout << "What is the trade risk?" << std::endl;
    std::cin >> TradeRisk;

    // Work out 1% of TradingAccountSize relative to TradeRisk. If TradeRisk is 5% then 
    //  5% of PositionSize needs to be MaxRiskPerTrade

    double TradeRiskAsPercentage = TradeRisk / WholeTradeRisk;
    double RiskMultiplyer = 100 / (TradeRiskAsPercentage * 100);

    std::cout << "Position size: " << MaxRiskPerTrade * RiskMultiplyer << std::endl;

    //std::cout << "Position Size: " << 

    
    return 0;
}
