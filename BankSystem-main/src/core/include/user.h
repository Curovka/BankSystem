// user.h
#ifndef USER_H
#define USER_H

#include "baseEntity.h"
#include "encryption.h"

enum class Gender { MALE, FEMALE };
enum class UserStatus { ACTIVE, INACTIVE, BLOCKED };

class User : public BaseEntity {
private:
    std::string roleId;
    std::string username;
    std::string email;
    std::string phone;
    std::string passwordHash;
    std::string firstName;
    std::string lastName;
    std::string patronymic;
    std::string passportSeries;
    std::string passportNumber;
    std::string passportIssueDate;
    std::string birthDate;
    Gender gender;
    double creditRating;
    UserStatus status;
    std::chrono::system_clock::time_point lastLogin;
    std::chrono::system_clock::time_point registrationDate;
    int failedLoginAttempts;
    
    std::unique_ptr<DataEncryptor> encryptor;

public:
    User(const std::string& username, const std::string& email, const std::string& password);
    virtual ~User() = default;
    
    bool authenticate(const std::string& password);
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    
    void updateProfile(const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& email);
    double calculateCreditRating();
    
    bool isActive() const { return status == UserStatus::ACTIVE; }
    bool isBlocked() const { return status == UserStatus::BLOCKED; }

    void blockUser();
    void unblockUser();
    
    std::string getFullName() const;

    // Паспортные данные с шифрованием
    void setPassportData(const std::string& series, const std::string& number);
    std::pair<std::string, std::string> getPassportData() const;

    // getters
    std::string getUsername() const { return username; }
    std::string getEmail() const { return email; }
    std::string getRoleId() const { return roleId; }
    double getCreditRating() const { return creditRating; }
    UserStatus getStatus() const { return status; }
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
};

#endif // USER_H