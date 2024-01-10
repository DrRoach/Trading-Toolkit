#include <string>
#include <iostream>
class Account;

class Input
{
    public:
        Input(Account* account);
    private:
        Account* _Account;

        void Help();
        void Quit();
        void PositionSizeCalculator();
};
