// creditRequest.h

#include <string>
#include <chrono>

#ifndef CREDITREQUEST.H
#define CREDITREQUEST.H

enum class CreditRequestStatus { PENDING, APPROVED, REJECTED, CANCELLED };

class CreditRequest {
private:
    std::string userId;
    std::string productId;
    double amount;
    CreditRequestStatus status;
    double monthly_payment;
    double interest_rate;
    std::string approvedBy;
    std::chrono::system_clock::time_point approvedAt;
    std::string rejectionReason;
    std::string createdAccountId; // Создание кредитного счета
    int term; // пока срок будет исчисляться в месяцах 
    
    // purpose //

public:
    CreditRequest(const std::string& userId, const std::string& productId, double amount, int term);
    
    double calculateMonthlyPayment();
    bool approve(const std::string& approvedBy);
    void reject(const std::string& reason);
    bool isValid() const;
    std::string createAccount(); // Создание кредитного счета
};

#endif
