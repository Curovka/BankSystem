// encryption.cpp

#include "../include/encryption.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>

// Константы SHA-256
const uint32_t SHA256_K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Константы AES S-Box
const unsigned char AES_SBOX[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

DataEncryptor::DataEncryptor(const std::string& passwordKey) {
    key = generateKey(passwordKey);
}

std::string DataEncryptor::hashPassword(const std::string& password) {
    //
}

// PBKDF2 реализация
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################
std::vector<unsigned char> DataEncryptor::generateKey(const std::string& password) {
    std::vector<unsigned char> salt = {0x73, 0x61, 0x6C, 0x74}; // "salt"
    return PBKDF2HMACSHA256(password, salt, 10000, 32); // 10000 - количество итераций; 32 - длина ключа
}

std::vector<unsigned char> DataEncryptor::PBKDF2HMACSHA256(const std::string& password, const std::vector<unsigned char>& salt, int iterations, int length) {
    
    std::vector<unsigned char> derivedKey;
    std::vector<unsigned char> passwordBytes(password.begin(), password.end());
    
    int block_count = (length + 31) / 32;
    
    for (int i = 1; i <= block_count; ++i) {
        
        //add random salt*** в будущем

        std::vector<unsigned char> saltWithIndex = salt;
        saltWithIndex.push_back((i >> 24) & 0xFF);
        saltWithIndex.push_back((i >> 16) & 0xFF);
        saltWithIndex.push_back((i >> 8) & 0xFF);
        saltWithIndex.push_back(i & 0xFF);
        
        //HMAC
        auto current = HMACSHA256(passwordBytes, saltWithIndex);
        auto result = current;
        
        //XOR
        for (int j = 1; j < iterations; ++j) {
            current = HMACSHA256(passwordBytes, current);
            for (size_t k = 0; k < result.size(); ++k) {
                result[k] ^= current[k];
            }
        }
        
        //обрезка
        derivedKey.insert(derivedKey.end(), result.begin(), result.end());
    }
    
    derivedKey.resize(length);
    return derivedKey;
}
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################



// HMAC-SHA256 реализация
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################
std::vector<unsigned char> DataEncryptor::HMACSHA256(
    const std::vector<unsigned char>& key, 
    const std::vector<unsigned char>& message) {
    
    const size_t BLOCK_SIZE = 64;
    std::vector<unsigned char> preparedKey(BLOCK_SIZE, 0);
    
    // Подготовка ключа
    if (key.size() > BLOCK_SIZE) { // Если ключ длиннее 64 байт - хешируем его
        auto hashedKey = SHA256(key); 
        std::copy(hashedKey.begin(), hashedKey.end(), preparedKey.begin());
    } else {
        std::copy(key.begin(), key.end(), preparedKey.begin());
    }
    
    std::vector<unsigned char> innerKey = preparedKey;
    for (size_t i = 0; i < BLOCK_SIZE; ++i) innerKey[i] ^= 0x36; // XOR с 0x36 (padding)
    
    //внутреннее хеширование
    std::vector<unsigned char> innerData = innerKey;
    innerData.insert(innerData.end(), message.begin(), message.end());
    auto innerHash = SHA256(innerData);
    
    //создание внешнего ключа
    std::vector<unsigned char> outerKey = preparedKey;
    for (size_t i = 0; i < BLOCK_SIZE; ++i) outerKey[i] ^= 0x5C; //XOR с 0x5C (padding)
    
    //финальное хеширование
    std::vector<unsigned char> outerData = outerKey;
    outerData.insert(outerData.end(), innerHash.begin(), innerHash.end());
    return SHA256(outerData);
}
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################



// SHA-256 реализация
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################
std::vector<unsigned char> DataEncryptor::SHA256(const std::vector<unsigned char>& input) {
    
    //первые 32 бита дробных частей квадратных корней первых 8 простых чисел (2 3 5 7 11 13 17 19).
    uint32_t h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    
    //Формат паддинга: исходные_данные + 0x80 + нули + длина_64бит
    uint64_t bitLength = input.size() * 8;
    std::vector<unsigned char> data = input;
    
    // Добавление 0x80
    data.push_back(0x80);

    //Добавление нулей до длины 448 бит (mod 512)
    while ((data.size() * 8) % 512 != 448) {
        data.push_back(0x00);
    }
    
    // Добавление длины сообщения (длина_64бит)
    for (int i = 7; i >= 0; --i) {
        data.push_back((bitLength >> (i * 8)) & 0xFF);
    }
    
    // Обработка блоков
    for (size_t chunk = 0; chunk < data.size(); chunk += 64) {
        uint32_t w[64] = {0};
        
        // Подготовка сообщения : преобразование 16 слов (32 бита каждое) из текущего блока
        for (int i = 0; i < 16; ++i) {
            w[i] = (data[chunk + i*4] << 24) | (data[chunk + i*4+1] << 16) | (data[chunk + i*4+2] << 8) | data[chunk + i*4+3];
        }
        
        // Расширение сообщения до 64 слов
        for (int i = 16; i < 64; ++i) {

            //Циклические сдвиги и XOR для рассеивания битов
            uint32_t s0 = ((w[i-15] >> 7) | (w[i-15] << 25)) ^ ((w[i-15] >> 18) | (w[i-15] << 14)) ^ (w[i-15] >> 3);
            uint32_t s1 = ((w[i-2] >> 17) | (w[i-2] << 15)) ^ ((w[i-2] >> 19) | (w[i-2] << 13)) ^ (w[i-2] >> 10);

            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }
        
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
        uint32_t e = h[4], f = h[5], g = h[6], h_val = h[7];
        
        //цикл сжатия для одностороннего хеширования
        for (int i = 0; i < 64; ++i) {
            uint32_t S1 = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h_val + S1 + ch + SHA256_K[i] + w[i];
            uint32_t S0 = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;
            
            h_val = g; g = f; f = e; e = d + temp1;
            d = c; c = b; b = a; a = temp1 + temp2;
        }
        
        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += h_val;
    }
    
    // Конвертирование хеш в байты
    std::vector<unsigned char> hash(32);
    for (int i = 0; i < 8; ++i) {
        hash[i*4] = (h[i] >> 24) & 0xFF;
        hash[i*4+1] = (h[i] >> 16) & 0xFF;
        hash[i*4+2] = (h[i] >> 8) & 0xFF;
        hash[i*4+3] = h[i] & 0xFF;
    }
    
    return hash;
}
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################
