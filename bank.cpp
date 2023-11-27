#include <iostream>
#include <iomanip>

class Account {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    Account(const std::string& num, const std::string& hold, double initialBalance)
        : accountNumber(num), accountHolder(hold), balance(initialBalance) {}

    virtual void displayDetails() const {
        std::cout << "Account Details for Account (ID: " << accountNumber << "):" << std::endl;
        std::cout << "\tHolder: " << accountHolder << std::endl;
        std::cout << "\tBalance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }
    
    void deposit(double amount) {
        balance += amount;
        std::cout << "Account Details after deposit:" << std::endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            std::cout << "Account Details after withdrawal:" << std::endl;
        } else {
            std::cout << "Insufficient funds." << std::endl;
        }
    }

    double theBalance() const {
        return balance;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& num, const std::string& hold, double initialBalance, double rate)
        : Account(num, hold, initialBalance), interestRate(rate) {}

    void displayDetails() const override {
        std::cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << std::endl;
        std::cout << "\tHolder: " << accountHolder << std::endl;
        std::cout << "\tBalance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "\tInterest Rate: " << std::fixed << std::setprecision(2) << (interestRate * 100) << "%" << std::endl;
    }

    void withdraw(double amount) override {
        if (amount <= theBalance() - 100) { //minimum balance for savings account 
            balance -= amount;
            std::cout << "Account Details after withdrawal:" << std::endl;
        } else {
            std::cout << "Insufficient funds or below minimum balance." << std::endl;
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(const std::string& num, const std::string& hold, double initialBalance, double limit)
        : Account(num, hold, initialBalance), overdraftLimit(limit) {}

    void displayDetails() const override {
        std::cout << "Account Details for Current Account (ID: " << accountNumber << "):" << std::endl;
        std::cout << "\tHolder: " << accountHolder << std::endl;
        std::cout << "\tBalance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "\tOverdraft Limit: $" << std::fixed << std::setprecision(2) << overdraftLimit << std::endl;
    }

    void withdraw(double amount) override {
        if (amount <= theBalance() + overdraftLimit) { //allows overdrafts up to a limit
            balance -= amount;
            std::cout << "Account Details after withdrawal:" << std::endl;
        } else {
            std::cout << "Overdraft limit exceeded." << std::endl;
        }
    }

    CurrentAccount operator+(const SavingsAccount& other) const { //overload + operator to allow transferring money between accounts 
        CurrentAccount result = *this;
        double transferAmount = 300.00;

        if (transferAmount <= other.theBalance()) { //checks if there is enough money to transfer 
            const_cast<SavingsAccount&>(other).withdraw(transferAmount);
            std::cout << "Account Details after transfer:" << std::endl;
            result.deposit(transferAmount);
        } else {
            std::cout << "Insufficient funds." << std::endl;
        }
        return result;
    }

};

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);
    savings.displayDetails();
    std::cout << std::endl;
    current.displayDetails();
    std::cout << std::endl;

    savings.deposit(500);
    current.withdraw(1000);
    savings.displayDetails();
    std::cout << std::endl;
    current.displayDetails();
    std::cout << std::endl;

    current = current + savings; //Transfer $300 from savings to current

    savings.displayDetails();
    std::cout << std::endl;
    current.displayDetails();
 
    return 0;
}
