// baseEntity.cpp
#include "../include/baseEntity.h"

// Объявление функции из uuid.cpp
namespace uuid {
    std::string generateUUIDv4();
}

BaseEntity::BaseEntity() {
    id = generateUUID();
    createdAt = std::chrono::system_clock::now();
    updatedAt = createdAt;
}

std::string BaseEntity::generateUUID() {
    return uuid::generateUUIDv4();
}

void BaseEntity::updateTimestamp() {
    updatedAt = std::chrono::system_clock::now();
}