
#include "baseEntity.h"
#include <chrono>
#include <memory>

#ifndef ACCOUNT.H
#define ACCOUNT.H

enum class Currency {RUB};
enum class AccountStatus {OPEN, BLOCKED, CLOSED};

class Account: public BaseEntity{
private:
    std::string userId;
    std::string productId;
    std::string accountNumber;
    double balance;
    double availableBalance; //tmp balance для операций
    Currency currency;
    double credit_limit;
    double interestRate;
    AccountStatus status;
    std::chrono::system_clock::time_point openedAt;
    std::chrono::system_clock::time_point closedAt;

public:
    Account(const std::string& userId, const std::string& productId);

    bool deposit(double amount);
    bool withdraw(double amount);
    bool transfer(std::unique_ptr<Account> toAccount, double amount);
    
    void calculateInterest();
    void block();
    void unblock();
    void close();
    bool IsActive() const {return status == AccountStatus::OPEN;}
    bool hasSufficientFunds(double amount) const { return availableBalance >= amount;}

    void generateAccountNumber();

    //getters
    double getAvailableBalance() const {return availableBalance;}

};

#endif
