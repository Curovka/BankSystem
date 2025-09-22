// card.h

#include <string>
#include <chrono>

#ifndef CARD.H
#define CARD.H

enum class CardType {DEBIT, CREDIT};
enum class CardStatus {ACTIVE, EXPIRED, BLOCKED, FROZEN};

class Card {
private:
    std::string accountId;
    std::string cardNumber;
    std::string holdeName;
    std::string expiryDate;
    std::string cvvHash;
    std::string pinHash;
    CardType cardType;
    CardStatus status;
    double dailyLimit;
    double montlyLimit;
    std::chrono::system_clock::time_point issuedAt;
    std::chrono::system_clock::time_point blockedAt;

    //transactions

public:
    Card(const std::string& accountId, const std::string& holderName, CardType type);

    bool validatePin(const std::string& pin);
    bool changePin(const std::string& oldPin, const std::string& newPin);
    void block();
    void unblock();
    void freeze();
    bool isExpired();
    bool isValidForTransaction(double amount);
    std::string getMaskedCardNumber();

    void generateCardNumber();
};

#endif