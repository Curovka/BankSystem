// account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "baseEntity.h"

enum class Currency { RUB, USD, EUR };
enum class AccountStatus { OPEN, BLOCKED, CLOSED };

class Account : public BaseEntity {
private:
    std::string userId;
    std::string productId;
    std::string accountNumber;
    double balance;
    double availableBalance;
    Currency currency;
    double creditLimit;
    double interestRate;
    AccountStatus status;
    std::chrono::system_clock::time_point openedAt;
    std::chrono::system_clock::time_point closedAt;

public:
    Account(const std::string& userId, const std::string& productId, Currency currency = Currency::RUB);

    virtual ~Account() = default; //пока логика не нужна

    bool deposit(double amount);
    bool withdraw(double amount);
    bool transfer(std::shared_ptr<Account> toAccount, double amount);
    
    void calculateInterest();
    void block();
    void unblock();
    void close();
    bool isActive() const { return status == AccountStatus::OPEN; }
    bool hasSufficientFunds(double amount) const { return availableBalance >= amount; }

    void setCreditLimit(double limit) { creditLimit = limit; updateTimestamp(); }
    void setInterestRate(double rate) { interestRate = rate; updateTimestamp(); }

    void generateAccountNumber();

    // getters
    std::string getUserId() const { return userId; }
    std::string getProductId() const { return productId; }
    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    double getAvailableBalance() const { return availableBalance; }
    Currency getCurrency() const { return currency; }
    double getCreditLimit() const { return creditLimit; }
    double getInterestRate() const { return interestRate; }
    AccountStatus getStatus() const { return status; }
};

#endif // ACCOUNT_H