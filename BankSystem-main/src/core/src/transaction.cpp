#include "transaction.h"

Transaction::Transaction(const std::string& from_account, const std::string& to_account, double amount, TransactionType type, Currency currency)
    : fromAccountId(from_account), toAccountId(to_account), amount(amount), transactionType(type), currency(currency) {
    
    status = TransactionStatus::PENDING;
    fee = 0.0;
    exchangeRate = 1.0;
    generateReferenceNumber();
}

bool Transaction::process() {
    if (!isValid()) {
        fail("Invalid transaction parameters");
        return false;
    }
    
    try {
        complete();
        return true;
    } catch (const std::exception& e) {
        fail(e.what());
        return false;
    }
}

void Transaction::generateReferenceNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    referenceNumber = "TR" + std::to_string(dis(gen)) + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
}

void Transaction::complete() {
    status = TransactionStatus::COMPLETED;
    completedAt = std::chrono::system_clock::now();
}

void Transaction::fail(const std::string& reason) {
    status = TransactionStatus::FAILED;
    failedReason = reason;
}

void Transaction::cancel() {
    if (status == TransactionStatus::PENDING) {
        status = TransactionStatus::CANCELLED;
    }
}

bool Transaction::isValid() const {
    return amount > 0 && !fromAccountId.empty() && !toAccountId.empty();
}

std::string Transaction::getTransactionDetails() const {
    return "Transaction " + referenceNumber + ": " + std::to_string(amount);
}