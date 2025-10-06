// encryption.cpp
#include "../include/encryption.h"
#include <sstream>
#include <iomanip>
#include <cstring>
#include <random>
#include <stdexcept>

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

// Константы AES Inverse S-Box
const unsigned char INV_SBOX[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

// Константы Rcon таблицы
const unsigned char Rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

DataEncryptor::DataEncryptor(const std::string& password) {
    key = generateKey(password);
    keyExpansion();
}

DataEncryptor::~DataEncryptor() {
    // Очистка чувствительных данных из памяти
    std::fill(key.begin(), key.end(), 0);
    std::fill(std::begin(round_keys), std::end(round_keys), 0);
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
    
    // Конвертируем хеш в байты
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
    for (size_t i = 0; i < key.size() && i < 32; i++) {
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



//AES шифрование реализация
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################

void DataEncryptor::AESEncrypt(const std::vector<unsigned char>& plaintext, const std::vector<unsigned char>& iv, std::vector<unsigned char>& ciphertext) {
    
    //проверка входных данных
    if (plaintext.size() % BLOCK_SIZE != 0) {
        throw std::invalid_argument("Plaintext must be multiple of block size");
    }
    
    //Выделение памяти для зашифрованного текста (того же размера, что и исходный)
    ciphertext.resize(plaintext.size());
    std::vector<unsigned char> prevblock = iv;
    
    for (size_t i = 0; i < plaintext.size(); i += BLOCK_SIZE) {
        std::vector<unsigned char> block(BLOCK_SIZE);
        
        //XOR с предыдущим блоком (CBC mode)
        for (size_t j = 0; j < BLOCK_SIZE; ++j) {
            block[j] = plaintext[i + j] ^ prevblock[j];
        }
        
        //штфрование блока + обновление предыдущего
        AESEncryptBlock(block.data(), &ciphertext[i]);
        prevblock.assign(&ciphertext[i], &ciphertext[i] + BLOCK_SIZE);
    }
}

void DataEncryptor::AESEncryptBlock(const unsigned char* input, unsigned char* output) {
    unsigned char state[BLOCK_SIZE];
    
    // Копируем входные данные в состояние
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        state[i] = input[i];
    }
    
    // Начальный раунд
    addRoundKey(state, 0);
    
    // Основные раунды
    for (int round = 1; round < 14; round++) {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, round);
    }
    
    // Финальный раунд
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, 14);
    
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        output[i] = state[i];
    }
}

//замена байтов для шифрования
void DataEncryptor::subBytes(unsigned char state[BLOCK_SIZE]) {
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        state[i] = AES_SBOX[state[i]];
    }
}

//Смещение строк матрицы для шифрования
void DataEncryptor::shiftRows(unsigned char state[BLOCK_SIZE]) {
    unsigned char temp[BLOCK_SIZE];
    
    // Row 0 - без сдвига
    temp[0] = state[0]; temp[4] = state[4]; temp[8] = state[8]; temp[12] = state[12];
    // Row 1 - сдвиг на 1
    temp[1] = state[5]; temp[5] = state[9]; temp[9] = state[13]; temp[13] = state[1];
    // Row 2 - сдвиг на 2
    temp[2] = state[10]; temp[6] = state[14]; temp[10] = state[2]; temp[14] = state[6];
    // Row 3 - сдвиг на 3
    temp[3] = state[15]; temp[7] = state[3]; temp[11] = state[7]; temp[15] = state[11];
    
    std::memcpy(state, temp, BLOCK_SIZE);
}

//смешивание столбцов для шифрования
void DataEncryptor::mixColumns(unsigned char state[BLOCK_SIZE]) {
    for (int i = 0; i < 4; i++) {
        unsigned char a[4];
        unsigned char b[4];
        unsigned char c;
        unsigned char h;
        
        for (c = 0; c < 4; c++) {
            a[c] = state[i * 4 + c];
            h = (unsigned char)((signed char)state[i * 4 + c] >> 7);
            b[c] = state[i * 4 + c] << 1;
            b[c] ^= 0x1B & h;
        }
        
        state[i * 4 + 0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
        state[i * 4 + 1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
        state[i * 4 + 2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
        state[i * 4 + 3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
    }
}

void DataEncryptor::addRoundKey(unsigned char state[BLOCK_SIZE], int round) {
    // Вычисление безопасного индекса
    const size_t max_safe_index = (sizeof(round_keys) / sizeof(round_keys[0])) * 4;
    const size_t start_index = round * BLOCK_SIZE;
    
    // Проверка границ
    if (start_index + BLOCK_SIZE > max_safe_index) {
        throw std::out_of_range("Round key index out of bounds");
    }
    
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        size_t key_index = start_index + i;
        uint32_t round_key_word = round_keys[key_index / 4];
        unsigned char key_byte = (round_key_word >> ((3 - (key_index % 4)) * 8)) & 0xFF;
        state[i] ^= key_byte;
    }
}
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################



//AES дешифрование реализация
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################
void DataEncryptor::AESDecrypt(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& iv, std::vector<unsigned char>& plaintext) {
    
    //проверка данных
    if (ciphertext.size() % BLOCK_SIZE != 0) {
        throw std::invalid_argument("Ciphertext must be multiple of block size");
    }
    
    plaintext.resize(ciphertext.size());
    std::vector<unsigned char> prev_block = iv;
    
    for (size_t i = 0; i < ciphertext.size(); i += BLOCK_SIZE) {
        // Дешифрование блока
        std::vector<unsigned char> block(BLOCK_SIZE);
        AESDecryptBlock(&ciphertext[i], block.data());
        
        // XOR с предыдущим блоком
        for (size_t j = 0; j < BLOCK_SIZE; ++j) {
            plaintext[i + j] = block[j] ^ prev_block[j];
        }
        
        prev_block.assign(&ciphertext[i], &ciphertext[i] + BLOCK_SIZE);
    }
}

void DataEncryptor::AESDecryptBlock(const unsigned char* input, unsigned char* output) {
    unsigned char state[BLOCK_SIZE];
    
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        state[i] = input[i];
    }
    
    // Начальный раунд (обратный порядок  для дешифрования)
    addRoundKey(state, 14);
    invShiftRows(state);
    invSubBytes(state);
    
    // Основные раунды
    for (int round = 13; round > 0; round--) {
        addRoundKey(state, round);
        invMixColumns(state);
        invShiftRows(state);
        invSubBytes(state);
    }
    
    // Финальный раунд
    addRoundKey(state, 0);
    
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        output[i] = state[i];
    }
}

//замена байтов для дешифрования
void DataEncryptor::invSubBytes(unsigned char state[BLOCK_SIZE]) {    
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        state[i] = INV_SBOX[state[i]];
    }
}

//Смещение строк матрицы для дешифрования
void DataEncryptor::invShiftRows(unsigned char state[BLOCK_SIZE]) {
    unsigned char temp[BLOCK_SIZE];
    
    // Row 0 - без сдвига
    temp[0] = state[0]; temp[4] = state[4]; temp[8] = state[8]; temp[12] = state[12];
    // Row 1 - обратный сдвиг на 1
    temp[1] = state[13]; temp[5] = state[1]; temp[9] = state[5]; temp[13] = state[9];
    // Row 2 - обратный сдвиг на 2
    temp[2] = state[10]; temp[6] = state[14]; temp[10] = state[2]; temp[14] = state[6];
    // Row 3 - обратный сдвиг на 3
    temp[3] = state[7]; temp[7] = state[11]; temp[11] = state[15]; temp[15] = state[3];
    
    std::memcpy(state, temp, BLOCK_SIZE);
}

//смешивание столбцов для дешифрования
void DataEncryptor::invMixColumns(unsigned char state[BLOCK_SIZE]) {
    for (int i = 0; i < 4; i++) {
        unsigned char a[4];
        
        for (int j = 0; j < 4; j++) {
            a[j] = state[i * 4 + j];
        }
        
        state[i * 4 + 0] = multiply(a[0], 0x0e) ^ multiply(a[1], 0x0b) ^ multiply(a[2], 0x0d) ^ multiply(a[3], 0x09);
        state[i * 4 + 1] = multiply(a[0], 0x09) ^ multiply(a[1], 0x0e) ^ multiply(a[2], 0x0b) ^ multiply(a[3], 0x0d);
        state[i * 4 + 2] = multiply(a[0], 0x0d) ^ multiply(a[1], 0x09) ^ multiply(a[2], 0x0e) ^ multiply(a[3], 0x0b);
        state[i * 4 + 3] = multiply(a[0], 0x0b) ^ multiply(a[1], 0x0d) ^ multiply(a[2], 0x09) ^ multiply(a[3], 0x0e);
    }
}

//вспомогательная функция для invMixColums
unsigned char DataEncryptor::multiply(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    unsigned char high_bit;
    
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= a;
        }
        
        high_bit = a & 0x80;
        a <<= 1;
        
        if (high_bit) {
            a ^= 0x1b;
        }
        
        b >>= 1;
    }
    
    return result;
}
//######################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------------
//######################################################################################################################################



//AES шифрование реализация (public)
std::string DataEncryptor::encryptAES(const std::string& plaintext) {
    // Генерируем IV (Initialization Vector)
    auto iv = generateRandomBytes(IV_SIZE);
    
    // Добавление padding (размер блока 16 байт) к plaintext
    std::vector<unsigned char> padded_plaintext(plaintext.begin(), plaintext.end());
    size_t padding = BLOCK_SIZE - (padded_plaintext.size() % BLOCK_SIZE);
    for (size_t i = 0; i < padding; ++i) {
        padded_plaintext.push_back(static_cast<unsigned char>(padding));
    }
    
    // Шифрование
    std::vector<unsigned char> ciphertext;
    AESEncrypt(padded_plaintext, iv, ciphertext);
    
    // Комбинирование IV + ciphertext в Base64
    std::vector<unsigned char> combined;
    combined.insert(combined.end(), iv.begin(), iv.end());
    combined.insert(combined.end(), ciphertext.begin(), ciphertext.end());
    
    //кодирование для передачи
    return base64Encode(combined);
}

//AES дешифрование реализация (public)
std::string DataEncryptor::decryptAES(const std::string& ciphertext) {

    //декодирование
    auto combined = base64Decode(ciphertext);

    //проверка данных
    if (combined.size() < IV_SIZE) {
        throw std::invalid_argument("Invalid ciphertext");
    }
    
    // Извлечение IV и ciphertext
    std::vector<unsigned char> iv(combined.begin(), combined.begin() + IV_SIZE);
    std::vector<unsigned char> encrypted_data(combined.begin() + IV_SIZE, combined.end());
    
    // Дешифрование
    std::vector<unsigned char> decrypted_data;
    AESDecrypt(encrypted_data, iv, decrypted_data);
    
    //Проверяем, что шифрование прошло успешно
    if (decrypted_data.empty()) {
        throw std::invalid_argument("Decryption failed");
    }
    
    //Удаление padding + проверка
    size_t padding = decrypted_data.back();
    if (padding > BLOCK_SIZE || padding > decrypted_data.size()) {
        throw std::invalid_argument("Invalid padding");
    }

    decrypted_data.resize(decrypted_data.size() - padding);
    
    //преобразование в строку    
    return std::string(decrypted_data.begin(), decrypted_data.end());
}

std::string DataEncryptor::hashPassword(const std::string& password) {
    auto salt = generateRandomBytes(16);
    int iterations = 100000;
    
    //основное хеширование
    auto hash = PBKDF2HMACSHA256(password, salt, iterations, 32); 
    
    //Формат: iterations:salt:hash (все в Base64)
    //100000:AbCdEfGhIjKlMnO:ZxYwVuTsRqPoNmLkJiHgFeDcBa
    return std::to_string(iterations) + ":" + 
           base64Encode(salt) + ":" + 
           base64Encode(hash);
}

bool DataEncryptor::verifyPassword(const std::string& password, const std::string& hash) {
    try {
        //разбор хеша
        //Формат: iterations:salt:hash
        //100000:AbCdEfGhIjKlMnO:ZxYwVuTsRqPoNmLkJiHgFeDcBa
        size_t pos1 = hash.find(':');
        size_t pos2 = hash.find(':', pos1 + 1);
        
        //проверка формата
        if (pos1 == std::string::npos || pos2 == std::string::npos) {
            return false;
        }
        
        //извлечение компонентов
        int iterations = std::stoi(hash.substr(0, pos1));
        auto salt = base64Decode(hash.substr(pos1 + 1, pos2 - pos1 - 1));
        auto stored_hash = base64Decode(hash.substr(pos2 + 1));
        
        //вычисление + сравнение хешей
        auto computed_hash = PBKDF2HMACSHA256(password, salt, iterations, 32);
        return computed_hash == stored_hash;
    } catch (...) {
        return false;
    }
}

//генерация вектора со случайными байтами
std::vector<unsigned char> DataEncryptor::generateRandomBytes(size_t length) {
    std::vector<unsigned char> result(length);
    std::random_device rd;
    std::uniform_int_distribution<unsigned short> dist(0, 255);
    
    for (size_t i = 0; i < length; ++i) {
        result[i] = static_cast<unsigned char>(dist(rd));
    }
    return result;
}

//кодирование
std::string DataEncryptor::base64Encode(const std::vector<unsigned char>& data) {
    std::string result;
    int i = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    //обработка данных блоками по 3 байта (24 бита), которые преобразуются в 4 символа Base64 (по 6 бит каждый).
    for (size_t n = 0; n < data.size(); n++) {
        char_array_3[i++] = data[n];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;                                        // Первые 6 бит первого байта
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);    // Последние 2 бита первого + первые 4 второго
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);    // Последние 4 бита второго + первые 2 третьего
            char_array_4[3] = char_array_3[2] & 0x3f;                                               // Последние 6 бит третьего байта
            
            for(i = 0; i < 4; i++) result += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    
    //если количество байтов не кратно 3, добавляется паддинг:
    if (i > 0) {
        for(int j = i; j < 3; j++) char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        
        for (int j = 0; j < i + 1; j++) result += base64_chars[char_array_4[j]];
        while(i++ < 3) result += '=';
    }
    
    return result;
}

//декодирование
std::vector<unsigned char> DataEncryptor::base64Decode(const std::string& encoded) {
    
    std::vector<unsigned char> result;
    int i = 0;
    unsigned char char_array_4[4], char_array_3[3];
    
    for (size_t n = 0; n < encoded.size(); n++) {
        if (encoded[n] == '=') break;
        
        char_array_4[i++] = encoded[n];
        if (i == 4) {
            //декодирование групп из 4 символов
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            
            // Преобразование 4 шестибитных значений в 3 байта (обратно кодированию)
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; i < 3; i++) result.push_back(char_array_3[i]);
            i = 0;
        }
    }
    
    //обработка неполных групп (учитывается padding)
    if (i > 0) {
        for (int j = i; j < 4; j++) char_array_4[j] = 0;
        for (int j = 0; j < 4; j++) char_array_4[j] = base64_chars.find(char_array_4[j]);
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        
        for (int j = 0; j < i - 1; j++) result.push_back(char_array_3[j]);
    }
    
    return result;
}

std::string DataEncryptor::maskCardNumber(const std::string& cardNumber) {
    if (cardNumber.length() != 16) return "****";
    return "**** **** **** " + cardNumber.substr(12);
}

std::string DataEncryptor::generateSecureRandom(size_t length) {
    auto random_bytes = generateRandomBytes(length);
    return base64Encode(random_bytes);
}