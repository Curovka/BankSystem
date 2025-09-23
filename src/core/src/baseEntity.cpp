//base entiry .cpp

#include "../include/baseEntity.h"
#include <iostream>

BaseEntity::BaseEntity() {
    id = generateUUID();
    createdAt = std::chrono::system_clock::now();
    updateAt = createdAt;
}

void BaseEntity::updateTimestamp() {
    updateAt = std::chrono::system_clock::now();
}