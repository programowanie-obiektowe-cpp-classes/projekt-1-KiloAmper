
#ifndef PRINTHELLO_HPP
#define PRINTHELLO_HPP

#include <string>
#include <vector>

    // ====== Struktura: Employee ======
    struct Employee
{
    std::string name;
    double      salary;
    std::string extraFeature;

    Employee(std::string n, double s, std::string ef);
    void display() const;
};

// ====== Struktura: Loan ======
struct Loan
{
    double amount;
    double monthlyPayment;
    int    monthsLeft;

    Loan(double amt, double payment, int months);
};

// ====== Klasa: Company ======
class Company
{
private:
    double                  cash;
    std::vector< Employee > engineers, warehouseWorkers, marketers, laborers;
    std::vector< Loan >     loans;
    int                     storedProducts;
    std::vector< double >   monthlyRevenueHistory;

    double calculateSalaries() const;
    double processLoans();
    void   displayStatus(double revenue, double profit) const;

public:
    Company();

    void displayEmployees() const;
    void hireEngineer(const std::string& name = "");
    void hireWarehouseWorker(const std::string& name = "");
    void hireMarketer(const std::string& name = "", int followers = rand() % 10000);
    void hireLaborer(const std::string& name = "", double shoeSize = rand() % 50 + 30);
    void takeLoan(double amount, int months);
    void endTurn();
};

#endif // PRINTHELLO_HPP