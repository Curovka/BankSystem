//user.h

#include "BaseEntity.h"
#include <chrono>
#include <string>

#ifndef USER.H
#define USER.H

enum class Gender { MALE, FEMALE};
enum class UserStatus { ACTIVE, INACTIVE, BLOCKED};

class User : public BaseEntity {
private:
    std::string role_id;
    std::string username;
    std::string email;
    std::string phone;
    std::string passwordHash;
    std::string firstName;
    std::string lastName;
    std::string patronymic;
    std::string passportSeries;
    std::string passportNumber;
    std::string passportIssueData;
    std::string birthDate;
    Gender gender;
    double creditRating;
    UserStatus status;
    std::chrono::system_clock::time_point lastLogin;
    std::chrono::system_clock::time_point registrationDate;

    //contacts // accounts // creditRequests // supportTickets

public:
    User(const std::string& username, const std::string& email, const std::string& password);

    bool authenticate(const std::string& password);
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);

    void updateProfile(const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& email);
    double calculateCreditRating();
    
    bool isActive() const {return status == UserStatus::ACTIVE;} // if inactive return inactive
    bool isBlocked() const {return status == UserStatus::BLOCKED;}
    std::string getFullName() const;

    //getters
    std::string getUserName() const {return username;}
    std::string getEmail() const {return email;}
    double gerCreditRating() const {return creditRating;}

};

#endif