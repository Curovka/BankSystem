#include "../include/bank_system.h"
#include <algorithm>

BankSystem::BankSystem() {
    encryptor = std::make_unique<DataEncryptor>("bank_system_key");
}

BankSystem::~BankSystem() {
    clearAllData();
}

void BankSystem::clearAllData() {
    std::lock_guard<std::mutex> lock1(usersMutex);
    std::lock_guard<std::mutex> lock2(accountsMutex);
    std::lock_guard<std::mutex> lock3(cardsMutex);
    std::lock_guard<std::mutex> lock4(transactionsMutex);
    std::lock_guard<std::mutex> lock5(creditRequestsMutex);
    
    users.clear();
    accounts.clear();
    cards.clear();
    transactions.clear();
    creditRequests.clear();
}

std::shared_ptr<User> BankSystem::registerUser(const std::string& username, const std::string& email, const std::string& password, const std::string& role) {
    std::lock_guard<std::mutex> lock(usersMutex);
    
    auto user = std::make_shared<User>(username, email, password);
    users[user->getId()] = user;
    return user;
}

std::shared_ptr<User> BankSystem::authenticateUser(const std::string& username, const std::string& password) {
    std::lock_guard<std::mutex> lock(usersMutex);
    
    for (const auto& [id, user] : users) {
        if (user->getUsername() == username && user->authenticate(password)) {
            return user;
        }
    }
    return nullptr;
}

std::shared_ptr<Account> BankSystem::createAccount(const std::string& userId, Currency currency) {
    std::lock_guard<std::mutex> lock1(usersMutex);
    std::lock_guard<std::mutex> lock2(accountsMutex);
    
    if (!users.count(userId)) return nullptr;
    
    auto account = std::make_shared<Account>(userId, "default_product", currency);
    accounts[account->getAccountNumber()] = account;
    return account;
}

std::shared_ptr<Card> BankSystem::createCard(const std::string& accountId, const std::string& holderName) {
    std::lock_guard<std::mutex> lock(cardsMutex);
    
    auto card = std::make_shared<Card>(accountId, holderName, CardType::DEBIT);
    cards[card->getCardNumber()] = card;
    return card;
}

std::vector<std::shared_ptr<Account>> BankSystem::findAccountsByUserId(const std::string& userId) {
    std::vector<std::shared_ptr<Account>> result;
    for (const auto& [number, account] : accounts) {
        if (account->getUserId() == userId) {
            result.push_back(account);
        }
    }
    return result;
}

std::shared_ptr<User> BankSystem::findUserByUsername(const std::string& username) {
    for (const auto& [id, user] : users) {
        if (user->getUsername() == username) {
            return user;
        }
    }
    return nullptr;
}

bool BankSystem::closeAccount(const std::string& accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end() && it->second->getBalance() == 0) {
        accounts.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<Transaction> BankSystem::createTransfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
    // pass
    return nullptr;
}

std::shared_ptr<CreditRequest> BankSystem::submitCreditRequest(const std::string& userId, double amount, int termMonths) {
    auto request = std::make_shared<CreditRequest>(userId, "credit_product", amount, termMonths);
    creditRequests[request->getUserId() + std::to_string(amount)] = request;
    return request;
}

std::shared_ptr<User> BankSystem::findUserById(const std::string& id) {
    auto it = users.find(id);
    return it != users.end() ? it->second : nullptr;
}

std::shared_ptr<Account> BankSystem::findAccountByNumber(const std::string& accountNumber) {
    auto it = accounts.find(accountNumber);
    return it != accounts.end() ? it->second : nullptr;
}

std::shared_ptr<Card> BankSystem::findCardByNumber(const std::string& cardNumber) {
    auto it = cards.find(cardNumber);
    return it != cards.end() ? it->second : nullptr;
}
