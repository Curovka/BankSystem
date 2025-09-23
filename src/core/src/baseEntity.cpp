//base entiry .cpp

#include "../include/baseEntity.h"
#include <iostream>
#include "uuid.cpp"

BaseEntity::BaseEntity() {
    id = generateUUID();
    createdAt = std::chrono::system_clock::now();
    updateAt = createdAt;
}

std::string BaseEntity::generateUUID() {
    return uuid::generateUUIDv4();
}

void BaseEntity::updateTimestamp() {
    updateAt = std::chrono::system_clock::now();
}
