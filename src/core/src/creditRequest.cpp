#include "../include/creditRequest.h"
#include <random>

CreditRequest::CreditRequest(const std::string& userId, const std::string& productId, double amount, int termMonths)
    : userId(userId), productId(productId), amount(amount), termMonths(termMonths) {
    
    status = CreditRequestStatus::PENDING;
    interestRate = 12.5;
    monthlyPayment = calculateMonthlyPayment();
}

double CreditRequest::calculateMonthlyPayment() {
    double monthly_rate = interestRate / 12 / 100;
    double coefficient = (monthly_rate * pow(1 + monthly_rate, termMonths)) / (pow(1 + monthly_rate, termMonths) - 1);
    
    return amount * coefficient;
}

bool CreditRequest::approve(const std::string& approvedBy) {
    if (status != CreditRequestStatus::PENDING) return false;
    
    this->approvedBy = approvedBy;
    approvedAt = std::chrono::system_clock::now();
    status = CreditRequestStatus::APPROVED;
    
    createdAccountId = createAccount();
    return true;
}

std::string CreditRequest::createAccount() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);
    return "40820" + std::to_string(dis(gen)); // Кредитный счет
}

void CreditRequest::reject(const std::string& reason) {
    if (status != CreditRequestStatus::PENDING) return;
    status = CreditRequestStatus::REJECTED;
    rejectionReason = reason;
}

bool CreditRequest::isValid() const {
    return amount > 0 && termMonths > 0 && status == CreditRequestStatus::PENDING;
}

