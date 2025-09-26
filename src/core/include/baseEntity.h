// baseEntity.h
#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "resources.h"

class BaseEntity {
protected:
    std::string id;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point updatedAt;

public:
    BaseEntity();
    virtual ~BaseEntity() = default;

    std::string generateUUID();
    void updateTimestamp();

    // getters
    std::string getId() const { return id; }
    std::chrono::system_clock::time_point getCreatedAt() const { return createdAt; }
    std::chrono::system_clock::time_point getUpdatedAt() const { return updatedAt; }
};

#endif // BASE_ENTITY_H
