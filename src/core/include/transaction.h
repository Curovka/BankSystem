// transaction.h
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "baseEntity.h"
#include "account.h"

enum class TransactionType { TRANSFER, DEPOSIT, WITHDRAWAL, PAYMENT };
enum class TransactionStatus { PENDING, COMPLETED, FAILED, CANCELLED };

class Transaction : public BaseEntity {
private:
    std::string fromAccountId;
    std::string toAccountId;
    double amount;
    Currency currency;
    TransactionType transactionType;
    TransactionStatus status;
    std::string description;
    std::string referenceNumber;
    double fee;
    double exchangeRate;
    std::chrono::system_clock::time_point completedAt;
    std::string failedReason;
    
public:
    Transaction(const std::string& fromAccount, const std::string& toAccount, 
                double amount, TransactionType type, Currency currency);
    
    bool process();
    void complete();
    void fail(const std::string& reason);
    void cancel();
    bool isValid() const;
    std::string getTransactionDetails() const;
    
    void generateReferenceNumber();

    // getters
    std::string getFromAccountId() const { return fromAccountId; }
    std::string getToAccountId() const { return toAccountId; }
    double getAmount() const { return amount; }
    TransactionType getTransactionType() const { return transactionType; }
    TransactionStatus getStatus() const { return status; }
    std::string getReferenceNumber() const { return referenceNumber; }
};

#endif // TRANSACTION_H
