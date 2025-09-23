//encryption.h
#include <vector>
#include <string>

#ifndef ENCRYPTION.H
#define ENCRYPTION.H

class DataEncryptor {
private:
    std::vector<unsigned char> key;

    // Криптографические примитивы
    std::vector<unsigned char> generateKey(const std::string& password);

    // AES реализация в будущем
    // PBKDF2 реализация в будущем
    // HMAC-SHA256 реализация в будущем
    // SHA-256 реализация в будущем
    
public:
    DataEncryptor(const std::string& password);
    
    std::string hashPassword(const std::string& password);
    bool verifyPassword(const std::string& password, const std::string& hash);
    std::string maskCardNumber(const std::string& cardNumber);
    std::string generateSecureRandom(size_t length);
};

#endif
