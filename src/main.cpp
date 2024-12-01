#include "PrintHello.hpp"
#include <iostream>

using namespace std;

int main()
{
    Company company;

    cout << "Witaj w symulacji przedsiebiorstwa!\n";

    string command;
    while (true)
    {
        cout << "\nWpisz komende (lp, zinz, zmag, zmkt, zrob, kred, kt, exit): ";
        cin >> command;

        if (command == "lp")
        {
            company.displayEmployees();
        }
        else if (command == "zinz")
        {
            company.hireEngineer();
        }
        else if (command == "zmag")
        {
            company.hireWarehouseWorker();
        }
        else if (command == "zmkt")
        {
            company.hireMarketer();
        }
        else if (command == "zrob")
        {
            company.hireLaborer();
        }
        else if (command == "kred")
        {
            double amount;
            int    months;
            cout << "Podaj kwote kredytu: ";
            cin >> amount;
            cout << "Podaj czas splaty w miesi¹cach: ";
            cin >> months;
            company.takeLoan(amount, months);
        }
        else if (command == "kt")
        {
            company.endTurn();
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            cout << "Nieznana komenda.\n";
        }
    }

    return 0;
}