// bankSystem.h
#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

#include "user.h"
#include "account.h"
#include "card.h"
#include "transaction.h"
#include "creditRequest.h"

class BankSystem {
private:
    std::unordered_map<std::string, std::shared_ptr<User>> users;
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts;
    std::unordered_map<std::string, std::shared_ptr<Card>> cards;
    std::unordered_map<std::string, std::shared_ptr<Transaction>> transactions;
    std::unordered_map<std::string, std::shared_ptr<CreditRequest>> creditRequests;
    
    mutable std::mutex usersMutex;
    mutable std::mutex accountsMutex;
    mutable std::mutex cardsMutex;
    mutable std::mutex transactionsMutex;
    mutable std::mutex creditRequestsMutex;
    
    std::unique_ptr<DataEncryptor> encryptor;
    
public:
    BankSystem();

    std::vector<std::shared_ptr<Account>> findAccountsByUserId(const std::string& userId);
    std::shared_ptr<User> findUserByUsername(const std::string& username);
    bool closeAccount(const std::string& accountNumber);
    
    // Управление пользователями
    std::shared_ptr<User> registerUser(const std::string& username, const std::string& email, const std::string& password, const std::string& role = "client");
    std::shared_ptr<User> authenticateUser(const std::string& username, const std::string& password);
    
    // Управление счетами
    std::shared_ptr<Account> createAccount(const std::string& userId, Currency currency = Currency::RUB);
    std::shared_ptr<Card> createCard(const std::string& accountId, const std::string& holderName);
    
    // Операции
    std::shared_ptr<Transaction> createTransfer(const std::string& fromAccount, const std::string& toAccount, double amount);
    
    // Кредиты
    std::shared_ptr<CreditRequest> submitCreditRequest(const std::string& userId, double amount, int termMonths);
    
    // Поиск
    std::shared_ptr<User> findUserById(const std::string& id);
    std::shared_ptr<Account> findAccountByNumber(const std::string& accountNumber);
    std::shared_ptr<Card> findCardByNumber(const std::string& cardNumber);
    
    // Статистика
    size_t getUsersCount() const { return users.size(); }
    size_t getAccountsCount() const { return accounts.size(); }
    size_t getCardsCount() const { return cards.size(); }
};

#endif // BANK_SYSTEM_H