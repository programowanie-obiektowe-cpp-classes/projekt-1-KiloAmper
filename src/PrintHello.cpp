#include "PrintHello.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime> // Potrzebne do losowania
#include <iomanip>
#include <iostream>
using namespace std;

// ====== Sta³e ======
const double CI            = 100.0;
const int    CMag          = 500;
const int    CMkt          = 50;
const int    CR            = 100;
const int    MAX_LOAN_TIME = 24;
const double BASE_INTEREST = 0.02;
const int    N             = 3;

// Lista imion i uczelni do wyboru
const std::vector< std::string > NAMES = {"Anna",
                                          "Jan",
                                          "Maria",
                                          "Krzysztof",
                                          "Piotr",
                                          "Joanna",
                                          "Pawe³",
                                          "Ewa",
                                          "Micha³",
                                          "Agnieszka",
                                          "Tomasz",
                                          "Magdalena",
                                          "Andrzej",
                                          "Katarzyna",
                                          "Marcin",
                                          "Monika"};

// uczelnie do wyboru
const vector< string > UNI = {
    "Politechnika Warszawska", "Akademia Gorniczo Hutnicza",
    "Politechnika Bialostocka", "Politechnika Gdanska"};

// Funkcja generuj¹ca losowe imie,uczelnie,prawo jazdy
std::string generateRandomName()
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(static_cast< unsigned int >(time(nullptr))); // Inicjalizacja generatora liczb pseudolosowych
        initialized = true;
    }
    int index = rand() % NAMES.size();
    return NAMES[index];
}

string generateRandomUni()
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(static_cast< unsigned int >(time(nullptr)));
        initialized = true;
    }
    int index = rand() % UNI.size();
    return UNI[index];
}

string generateRandomLicense()
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(static_cast< unsigned int >(time(nullptr)));
        initialized = true;
    }
    double    index = rand() % 2;
    string odp;
    if (index > 0)
    {
        odp = "Czy posiada prawo jazdy na wozek widlowy: NIE";
        return odp;
    }
    else
    {
        odp = "Czy posiada prawo jazdy na wozek widlowy: TAK";
        return odp;
    }
}


// ====== Implementacja Employee ======
Employee::Employee(string n, double s, string ef) : name(n), salary(s), extraFeature(ef)
{}

void Employee::display() const
{
    cout << "- " << name << ", pensja: " << salary << " zl, cecha: " << extraFeature << "\n";
}

// ====== Implementacja Loan ======
Loan::Loan(double amt, double payment, int months) : amount(amt), monthlyPayment(payment), monthsLeft(months)
{}

// ====== Implementacja Company ======
Company::Company() : cash(10000.0), storedProducts(0)
{
    engineers.emplace_back("Jan", 5000.0, "Politechnika Warszawska");
    warehouseWorkers.emplace_back("Natalia", 3000.0, "Prawo jazdy na wozek widlowy : Tak");
    marketers.emplace_back("Maria", 4000.0, "1000");
    laborers.emplace_back("Krzysztof", 2000.0, "42.5");
}

void Company::displayEmployees() const
{
    cout << "\n=== Lista pracownikow ===\n";
    cout << "Inzynierowie:\n";
    for (const auto& e : engineers)
        e.display();
    cout << "Magazynierzy:\n";
    for (const auto& e : warehouseWorkers)
        e.display();
    cout << "Marketerzy:\n";
    for (const auto& e : marketers)
        e.display();
    cout << "Robotnicy:\n";
    for (const auto& e : laborers)
        e.display();
    cout << "=========================\n";
}

void Company::hireEngineer(const std::string& name)
{
    engineers.emplace_back(name.empty() ? generateRandomName() : name, 5000.0, generateRandomUni());
}

void Company::hireWarehouseWorker(const std::string& name)
{
    warehouseWorkers.emplace_back(name.empty() ? generateRandomName() : name,
                                  3000.0,generateRandomLicense());
}

void Company::hireMarketer(const std::string& name, int followers)
{
    marketers.emplace_back(
        name.empty() ? generateRandomName() : name, 4000.0, std::to_string(followers) + " obserwujacych");
}

void Company::hireLaborer(const std::string& name, double shoeSize)
{
    laborers.emplace_back(
        name.empty() ? generateRandomName() : name, 2000.0, std::to_string(shoeSize) + " (rozmiar buta)");
}

void Company::takeLoan(double amount, int months)
{
    if (months > MAX_LOAN_TIME)
    {
        cout << "Nie mozna wziac kredytu na wiecej niz " << MAX_LOAN_TIME << " miesiecy.\n";
        return;
    }
    double interestRate   = BASE_INTEREST + 0.01 * months;
    double monthlyPayment = (amount * (1 + interestRate)) / months;
    loans.emplace_back(amount, monthlyPayment, months);
    cash += amount;
}

void Company::endTurn()
{
    double productPrice       = engineers.size() * CI;
    int    warehouseCapacity  = warehouseWorkers.size() * CMag;
    int    demand             = marketers.size() * CMkt;
    int    possibleProduction = laborers.size() * CR;

    int produced = min(possibleProduction, warehouseCapacity);
    storedProducts += produced;

    int sold = min(demand, storedProducts);
    storedProducts -= sold;

    double revenue       = sold * productPrice;
    double totalSalaries = calculateSalaries();
    double loanPayments  = processLoans();

    double profit = revenue - totalSalaries - loanPayments;
    cash += profit;

    monthlyRevenueHistory.push_back(revenue);
    if (monthlyRevenueHistory.size() > N)
    {
        monthlyRevenueHistory.erase(monthlyRevenueHistory.begin());
    }

    displayStatus(revenue, profit);

    if (cash < 0)
    {
        cout << "\n=== Bankructwo! ===\n";
        exit(0);
    }
}

double Company::calculateSalaries() const
{
    double total = 0;
    for (const auto& e : engineers)
        total += e.salary;
    for (const auto& e : warehouseWorkers)
        total += e.salary;
    for (const auto& e : marketers)
        total += e.salary;
    for (const auto& e : laborers)
        total += e.salary;
    return total;
}

double Company::processLoans()
{
    double totalPayment = 0;
    for (auto& loan : loans)
    {
        if (loan.monthsLeft > 0)
        {
            cash -= loan.monthlyPayment;
            loan.monthsLeft--;
            totalPayment += loan.monthlyPayment;
        }
    }
    return totalPayment;
}

void Company::displayStatus(double revenue, double profit) const
{
    cout << "\n=== Podsumowanie miesiaca ===\n";
    cout << "Przychod: " << revenue << " zl\n";
    cout << "Zysk: " << profit << " zl\n";
    cout << "Gotowka: " << cash << " zl\n";
    cout << "Produkty na magazynie: " << storedProducts << "\n";
    cout << "=============================\n";
}
