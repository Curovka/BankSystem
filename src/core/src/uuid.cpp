//функция генерации UUID
//
//UUID_v4 имеет формат: xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx
//4 - версия 
//y - вариант
//1414f37d-bb9f-4fe6-89d5-90749291a1e0
//03063eb0-2288-47e0-a525-fda6d2b01198
//c215f05a-8854-49cb-bdd3-e91fdf5d7a66
//a3751ed6-860d-4947-bfee-78baeeed2383
//
//

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
