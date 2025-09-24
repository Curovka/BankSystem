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

    // Константы AES
    static const size_t BLOCK_SIZE = 16;
    static const size_t KEY_SIZE = 32;
    static const size_t IV_SIZE = 16;
    static const size_t NUM_ROUNDS = 14;
    uint32_t round_keys[60];

    // AES реализация
    void AESEncrypt(const std::vector<unsigned char>& plaintext, const std::vector<unsigned char>& iv, std::vector<unsigned char>& ciphertext);
    void AESDecrypt(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& iv, std::vector<unsigned char>& plaintext);
    void AESEncryptBlock(const unsigned char* input, unsigned char* output);
    void AESDecryptBlock(const unsigned char* input, unsigned char* output);

    //вспомогательные функции для шифрования и дешифрования
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
    
public:
    DataEncryptor(const std::string& password);
    
    std::string hashPassword(const std::string& password);
    bool verifyPassword(const std::string& password, const std::string& hash);
    std::string maskCardNumber(const std::string& cardNumber);
    std::string generateSecureRandom(size_t length);
};

#endif
