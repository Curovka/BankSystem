// uuid.cpp
#include "resources.h"

namespace uuid {
    std::string generateUUIDv4() {
        std::array<uint8_t, 16> bytes;
        std::random_device rd;
        std::uniform_int_distribution<uint8_t> dis(0, 255);
        
        for (size_t i = 0; i < 16; ++i) {
            bytes[i] = dis(rd);
        }
        
        // Установка версии 4 и варианта 2
        bytes[6] = (bytes[6] & 0x0F) | 0x40;
        bytes[8] = (bytes[8] & 0x3F) | 0x80;
        
        // Преобразование в строку
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        
        for (size_t i = 0; i < 16; ++i) {
            if (i == 4 || i == 6 || i == 8 || i == 10) ss << "-";
            ss << std::setw(2) << static_cast<int>(bytes[i]);
        }
        
        return ss.str();
    }
}