// creditRequest.h
#ifndef CREDIT_REQUEST_H
#define CREDIT_REQUEST_H

#include "resources.h"

enum class CreditRequestStatus { PENDING, APPROVED, REJECTED, CANCELLED };

class CreditRequest {
private:
    std::string userId;
    std::string productId;
    double amount;
    int termMonths;
    CreditRequestStatus status;
    double monthlyPayment;
    double interestRate;
    std::string approvedBy;
    std::chrono::system_clock::time_point approvedAt;
    std::string rejectionReason;
    std::string createdAccountId;
    
public:
    CreditRequest(const std::string& userId, const std::string& productId, 
                 double amount, int termMonths);
    
    double calculateMonthlyPayment();
    bool approve(const std::string& approvedBy);
    void reject(const std::string& reason);
    bool isValid() const;
    std::string createAccount();

    // getters
    std::string getUserId() const { return userId; }
    std::string getProductId() const { return productId; }
    double getAmount() const { return amount; }
    int getTermMonths() const { return termMonths; }
    CreditRequestStatus getStatus() const { return status; }
    double getMonthlyPayment() const { return monthlyPayment; }
};

#endif // CREDIT_REQUEST_H
