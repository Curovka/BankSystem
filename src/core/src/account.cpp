#include "../include/account.h"
#include <random>

Account::Account(const std::string& user_id, const std::string& product_id, Currency currency) 
    : userId(user_id), productId(product_id), currency(currency) {
    
    balance = 0.0;
    availableBalance = 0.0;
    creditLimit = 0.0;
    interestRate = 0.0;
    status = AccountStatus::OPEN;
    openedAt = std::chrono::system_clock::now();
    
    generateAccountNumber();
}

void Account::generateAccountNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);
    
    accountNumber = "40817" + std::to_string(dis(gen)); // 40817 - тип счета
}

bool Account::deposit(double amount) {
    if (amount <= 0 || !isActive()) return false;
    
    balance += amount;
    availableBalance += amount;
    updateTimestamp();
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || !hasSufficientFunds(amount) || !isActive()) return false;
    
    balance -= amount;
    availableBalance -= amount;
    updateTimestamp();
    return true;
}

bool Account::transfer(std::shared_ptr<Account> toAccount, double amount) {
    if (!isActive() || !toAccount->isActive() || amount <= 0) 
        return false;
    
    if (!hasSufficientFunds(amount)) 
        return false;
    
    if (withdraw(amount)) {
        if (toAccount->deposit(amount)) {
            updateTimestamp();
            return true;
        } else {
            // Откат если депозит не удался
            deposit(amount);
            return false;
        }
    }
    return false;
}

void Account::calculateInterest() {
    if (!isActive() || interestRate <= 0) return;
    
    double interest = balance * (interestRate / 100.0) / 12.0; // Ежемесячный процент
    deposit(interest);
}

void Account::block() {
    status = AccountStatus::BLOCKED;
    updateTimestamp();
}

void Account::unblock() {
    if (status == AccountStatus::BLOCKED) {
        status = AccountStatus::OPEN;
        updateTimestamp();
    }
}

void Account::close() {
    if (balance == 0.0) {
        status = AccountStatus::CLOSED;
        closedAt = std::chrono::system_clock::now();
        updateTimestamp();
    }
}