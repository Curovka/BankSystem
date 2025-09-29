// user.cpp

#include "../include/user.h"
#include <chrono>
#include <algorithm>

namespace BankConfig {
    const int MAX_LOGIN_ATTEMPTS = 5;
}

User::User(const std::string& username, const std::string& email, const std::string& password) 
    : username(username), email(email) {
    
    encryptor = std::make_unique<DataEncryptor>("bank_master_key_2024");
    passwordHash = encryptor->hashPassword(password);
    status = UserStatus::ACTIVE;
    creditRating = 0.0;
    failedLoginAttempts = 0;
    registrationDate = std::chrono::system_clock::now();
    lastLogin = registrationDate;
}

bool User::authenticate(const std::string& password) {
    if (isBlocked()) return false;
    
    if (encryptor->verifyPassword(password, passwordHash)) {
        failedLoginAttempts = 0;
        lastLogin = std::chrono::system_clock::now();
        updateTimestamp();
        return true;
    }
    
    failedLoginAttempts++;
    if (failedLoginAttempts >= BankConfig::MAX_LOGIN_ATTEMPTS) {
        blockUser();
    }
    
    return false;
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    if (!authenticate(oldPassword)) return false;
    
    passwordHash = encryptor->hashPassword(newPassword);
    updateTimestamp();
    return true;
}

void User::updateProfile(const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& email) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->email = email;
    updateTimestamp();
}

void User::setPassportData(const std::string& series, const std::string& number) {
    passportSeries = encryptor->encryptAES(series);
    passportNumber = encryptor->encryptAES(number);
    updateTimestamp();
}

std::pair<std::string, std::string> User::getPassportData() const {
    return {
        encryptor->decryptAES(passportSeries),
        encryptor->decryptAES(passportNumber)
    };
}

double User::calculateCreditRating() {
    // Упрощенный алгоритм скоринга
    double rating = 500.0; // Базовый рейтинг
    
    // Логика расчета на основе истории операций, возраста и т.д.
    auto now = std::chrono::system_clock::now();
    auto regDuration = now - registrationDate;
    auto yearsRegistered = std::chrono::duration_cast<std::chrono::hours>(regDuration).count() / 8760.0;
    
    rating += std::min(yearsRegistered * 50.0, 200.0); // Максимум +200 за стаж
    
    creditRating = std::max(300.0, std::min(850.0, rating)); // Ограничение 300-850
    updateTimestamp();
    
    return creditRating;
}

void User::blockUser() {
    status = UserStatus::BLOCKED;
    updateTimestamp();
}

void User::unblockUser() {
    status = UserStatus::ACTIVE;
    failedLoginAttempts = 0;
    updateTimestamp();
}

std::string User::getFullName() const {
    return firstName + " " + lastName + (patronymic.empty() ? "" : " " + patronymic);

}
