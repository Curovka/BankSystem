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
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// Константы Rcon таблицы
const unsigned char Rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
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



//AES Key Expansion реализация
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################
void DataEncryptor::keyExpansion() {
    int Nk = 8; //Количество 32-битных слов в исходном ключе (256 бит / 32 = 8 слов)
    int Nr = 14; //Количество раундов шифрования
    int Nb = 4;  //Размер блока в словах (128 бит = 4 слова)
    
    std::memset(round_keys, 0, sizeof(round_keys));
    
    //Копирование исходного ключа в начало расширенного ключа
    for (int i = 0; i < key.size() && i < 32; i++) {
        round_keys[i] = key[i];
    }
    
    //Основной цикл расширения ключа
    for (int i = Nk; i < Nb * (Nr + 1); i++) {
        unsigned char temp[4];
        
        for (int j = 0; j < 4; j++) {
            temp[j] = round_keys[4 * (i - 1) + j];
        }
        
        if (i % Nk == 0) {
            rotWord(temp);
            subWord(temp);
            temp[0] ^= Rcon[i / Nk];
        } 
        else if (Nk > 6 && i % Nk == 4) {
            subWord(temp);
        }

        for (int j = 0; j < 4; j++) {
            round_keys[4 * i + j] = round_keys[4 * (i - Nk) + j] ^ temp[j];
        }
    }
}

//циклический сдвиг байтов
void DataEncryptor::rotWord(unsigned char word[4]) {
    unsigned char temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

//замена байтов через S-Box
void DataEncryptor::subWord(unsigned char word[4]) {
    for (int i = 0; i < 4; i++) {
        word[i] = AES_SBOX[word[i]];
    }
}
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################
