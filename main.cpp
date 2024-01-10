#include <iostream>
#include <fstream>
#include <string>
#include "Account.h"
#include "Input.h"

int main()
{
    Account* account = new Account();
    account->Setup();

    std::cout << "Trade risk is set to " << account->GetMaxRiskPercentage() << "%" << std::endl;
    std::cout << "Max risk per trade is: " << account->GetRiskPerTrade() << std::endl;

    std::cout << "You can lose " << account->ConsecutiveLosses() << " trades in a row" << std::endl;

    Input* input = new Input(account);

    return 0;
}
