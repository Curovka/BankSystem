// card.h
#ifndef CARD_H
#define CARD_H

#include "resources.h"
#include "encryption.h"

enum class CardType { DEBIT, CREDIT };
enum class CardStatus { ACTIVE, EXPIRED, BLOCKED, FROZEN };

class Card {
private:
    std::string accountId;
    std::string cardNumber;
    std::string holderName;
    std::string expiryDate;
    std::string cvvHash;
    std::string pinHash;
    CardType cardType;
    CardStatus status;
    double dailyLimit;
    double monthlyLimit;
    double dailyUsed;
    double monthlyUsed;
    std::chrono::system_clock::time_point issuedAt;
    std::chrono::system_clock::time_point blockedAt;
    
    std::unique_ptr<DataEncryptor> encryptor;

public:
    Card(const std::string& accountId, const std::string& holderName, CardType type);
    ~Card() = default; //аналогично account

    bool validatePIN(const std::string& pin);
    bool changePIN(const std::string& oldPin, const std::string& newPin);
    void block();
    void unblock();
    void freeze();
    bool isExpired() const;
    bool isValidForTransaction(double amount) const;
    std::string getMaskedCardNumber() const;

    void generateCardNumber();

    // getters
    std::string getAccountId() const { return accountId; }
    std::string getCardNumber() const { return cardNumber; }
    std::string getHolderName() const { return holderName; }
    CardType getCardType() const { return cardType; }
    CardStatus getStatus() const { return status; }
    bool isActive() const { return status == CardStatus::ACTIVE; }
};

#endif // CARD_H