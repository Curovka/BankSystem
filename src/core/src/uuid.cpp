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

#include <random>
#include <sstream>
#include <array>
#include <iomanip>
#include <iostream>

namespace uuid {
    std::string generateUUIDv4() {
        std::array<uint8_t, 16> bytes;
        std::random_device rd; //для "безопасных" случайных чисел
        
        //генерация 128 бит случайности и создание массива байтов

        for (size_t i = 0; i < 16; ++i) {
            if (i % sizeof(std::random_device::result_type) == 0) {
                auto random_value = rd();
                
                // Копирование random_value побайтово
                for (size_t j = 0; j < sizeof(random_value) && i + j < 16; ++j) {
                    bytes[i + j] = static_cast<uint8_t>((random_value >> (j * 8)) & 0xFF);
                }
            }
        }
        
        //устанавка версию 4 и вариант 2
        bytes[6] = (bytes[6] & 0x0F) | 0x40;
        bytes[8] = (bytes[8] & 0x3F) | 0x80;
        
        //преобразование в строку
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        
        for (size_t i = 0; i < 16; ++i) {
            if (i == 4 || i == 6 || i == 8 || i == 10) ss << "-";
            ss << std::setw(2) << static_cast<int>(bytes[i]);
        }
        
        return ss.str();
    }
}
