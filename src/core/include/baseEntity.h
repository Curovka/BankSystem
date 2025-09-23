// base_entity.h

#include <string>
#include <chrono>

#ifndef BASEENTITY.H
#define BASEENTITY.H

class BaseEntity {
protected:
    std::string id;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point updateAt;

public:
    BaseEntity();

    std::string generateUUID();

    //getters
    std::string getId() const { return id;}
    std::chrono::system_clock::time_point getCreatedAt() const { return createdAt; }
    std::chrono::system_clock::time_point getUpdatedAt() const { return updateAt; }
};


#endif
