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
    std::vector<unsigned char> PBKDF2HMACSHA256(const std::string& password, const std::vector<unsigned char>& salt, int iterations, int length); 
    std::vector<unsigned char> HMACSHA256(const std::vector<unsigned char>& key, const std::vector<unsigned char>& message);
    std::vector<unsigned char> SHA256(const std::vector<unsigned char>& input);

    // AES реализация в будущем
    void keyExpansion();
    void rotWord(unsigned char word[4]);
    void subWord(unsigned char word[4]);
    
public:
    DataEncryptor(const std::string& password);
    
    std::string hashPassword(const std::string& password);
    bool verifyPassword(const std::string& password, const std::string& hash);
    std::string maskCardNumber(const std::string& cardNumber);
    std::string generateSecureRandom(size_t length);
};

#endif
