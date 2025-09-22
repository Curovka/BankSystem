// base_entity.h

#include <string>
#include <chrono>

#ifndef BASEENTITY.H
#define BASEENTITY.H

class BaseEntity {
protected:
    std::string id;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point update_at;

public:
    BaseEntity();

    std::string generateUUID();

    //getters
    std::string getId() const { return id;}
    std::chrono::system_clock::time_point getCreatedAt() const { return created_at; }
    std::chrono::system_clock::time_point getUpdatedAt() const { return update_at; }
};

#endif