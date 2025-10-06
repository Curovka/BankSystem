#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <vector>
#include <cstddef>
#include <cstdint>
#include <string>


class DataEncryptor {
private:
    std::vector<unsigned char> key;
    static const size_t BLOCK_SIZE = 16;
    static const size_t KEY_SIZE = 32;
    static const size_t IV_SIZE = 16;
    static const size_t NUM_ROUNDS = 14;
    uint32_t round_keys[60];

    // Приватные криптографические примитивы
    std::vector<unsigned char> generateKey(const std::string& password);
    std::vector<unsigned char> PBKDF2HMACSHA256(const std::string& password, const std::vector<unsigned char>& salt, int iterations, int length);
    std::vector<unsigned char> HMACSHA256(const std::vector<unsigned char>& key, const std::vector<unsigned char>& message);
    std::vector<unsigned char> SHA256(const std::vector<unsigned char>& input);

    // AES реализация
    void AESEncrypt(const std::vector<unsigned char>& plaintext, const std::vector<unsigned char>& iv, std::vector<unsigned char>& ciphertext);
    void AESDecrypt(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& iv, std::vector<unsigned char>& plaintext);
    void AESEncryptBlock(const unsigned char* input, unsigned char* output);
    void AESDecryptBlock(const unsigned char* input, unsigned char* output);
    
    void subBytes(unsigned char state[BLOCK_SIZE]);
    void invSubBytes(unsigned char state[BLOCK_SIZE]);
    void shiftRows(unsigned char state[BLOCK_SIZE]);
    void invShiftRows(unsigned char state[BLOCK_SIZE]);
    void mixColumns(unsigned char state[BLOCK_SIZE]);
    void invMixColumns(unsigned char state[BLOCK_SIZE]);
    unsigned char multiply(unsigned char a, unsigned char b);
    void addRoundKey(unsigned char state[BLOCK_SIZE], int round);

    void keyExpansion();
    void rotWord(unsigned char word[4]);
    void subWord(unsigned char word[4]);
    
    // Вспомогательные функции
    std::vector<unsigned char> generateRandomBytes(size_t length);
    std::string base64Encode(const std::vector<unsigned char>& data);
    std::vector<unsigned char> base64Decode(const std::string& data);
    
public:
    DataEncryptor(const std::string& password);
    ~DataEncryptor();
    
    std::string encryptAES(const std::string& plaintext);
    std::string decryptAES(const std::string& ciphertext);
    std::string hashPassword(const std::string& password);
    bool verifyPassword(const std::string& password, const std::string& hash);
    std::string maskCardNumber(const std::string& cardNumber);
    std::string generateSecureRandom(size_t length);
};

#endif //ENCRYPTION_H