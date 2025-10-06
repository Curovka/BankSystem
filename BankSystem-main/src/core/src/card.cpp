#include "../include/card.h"
#include <ctime>
#include <chrono>

Card::Card(const std::string& accountId, const std::string& holderName, CardType type) 
    : accountId(accountId), holderName(holderName), cardType(type) {
    
    encryptor = std::make_unique<DataEncryptor>("card_master_key");
    status = CardStatus::ACTIVE;
    dailyLimit = 150000.0;
    monthlyLimit = 1000000.0;
    dailyUsed = 0.0;
    monthlyUsed = 0.0;
    issuedAt = std::chrono::system_clock::now();
    
    generateCardNumber();
    
    // Генерация срока действия (3 года)
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    now->tm_year += 3;
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%m/%Y", now);
    expiryDate = buffer;
}

void Card::generateCardNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    
    cardNumber = "4276" + std::to_string(dis(gen)) + std::to_string(dis(gen)) + std::to_string(dis(gen));
}

bool Card::validatePIN(const std::string& pin) {
    return encryptor->verifyPassword(pin, pinHash);
}

bool Card::changePIN(const std::string& oldPin, const std::string& newPin) {
    if (validatePIN(oldPin)) {
        pinHash = encryptor->hashPassword(newPin);
        return true;
    }
    return false;
}

void Card::block() {
    status = CardStatus::BLOCKED;
    blockedAt = std::chrono::system_clock::now();
}

void Card::unblock() {
    if (status == CardStatus::BLOCKED) {
        status = CardStatus::ACTIVE;
    }
}

void Card::freeze() {
    status = CardStatus::FROZEN;
}

bool Card::isExpired() const {
    // [pass]
    return false;
}

bool Card::isValidForTransaction(double amount) const {
    if (!isActive() || isExpired()) return false;
    
    auto now = std::chrono::system_clock::now();
    auto today = std::chrono::time_point_cast<std::chrono::hours>(now);
    
    return (dailyUsed + amount <= dailyLimit) && (monthlyUsed + amount <= monthlyLimit);
}

std::string Card::getMaskedCardNumber() const {
    if (cardNumber.length() < 16) return "****";
    return "**** **** **** " + cardNumber.substr(12);
}

