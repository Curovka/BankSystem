// localization.h
#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include "resources.h"
#include <unordered_map>

enum class Language { RU, EN };

class Localization {
private:
    static inline Language currentLanguage = Language::RU;
    static inline std::unordered_map<std::string, std::unordered_map<Language, std::string>> translations = {
        // Main menu
        {"bank_system", {{Language::RU, "БАНКОВСКАЯ СИСТЕМА"}, {Language::EN, "BANK SYSTEM"}}},
        {"welcome", {{Language::RU, "Добро пожаловать, "}, {Language::EN, "Welcome, "}}},
        {"registration", {{Language::RU, "Регистрация"}, {Language::EN, "Registration"}}},
        {"login", {{Language::RU, "Вход в систему"}, {Language::EN, "Login"}}},
        {"system_stats", {{Language::RU, "Статистика системы"}, {Language::EN, "System Statistics"}}},
        {"exit", {{Language::RU, "Выход"}, {Language::EN, "Exit"}}},
        {"account_management", {{Language::RU, "Управление счетами"}, {Language::EN, "Account Management"}}},
        {"operations", {{Language::RU, "Операции"}, {Language::EN, "Operations"}}},
        {"credit_requests", {{Language::RU, "Кредитные заявки"}, {Language::EN, "Credit Requests"}}},
        {"profile", {{Language::RU, "Профиль"}, {Language::EN, "Profile"}}},
        {"logout", {{Language::RU, "Выйти из системы"}, {Language::EN, "Logout"}}},
        
        // Authentication
        {"username", {{Language::RU, "Логин"}, {Language::EN, "Username"}}},
        {"email", {{Language::RU, "Email"}, {Language::EN, "Email"}}},
        {"password", {{Language::RU, "Пароль"}, {Language::EN, "Password"}}},
        {"registration_success", {{Language::RU, "Регистрация успешна! ID пользователя: "}, {Language::EN, "Registration successful! User ID: "}}},
        {"registration_error", {{Language::RU, "Ошибка регистрации!"}, {Language::EN, "Registration error!"}}},
        {"login_success", {{Language::RU, "Вход выполнен успешно!"}, {Language::EN, "Login successful!"}}},
        {"login_error", {{Language::RU, "Неверный логин или пароль!"}, {Language::EN, "Invalid username or password!"}}},
        
        // System stats
        {"users_count", {{Language::RU, "Пользователей"}, {Language::EN, "Users"}}},
        {"accounts_count", {{Language::RU, "Счетов"}, {Language::EN, "Accounts"}}},
        {"cards_count", {{Language::RU, "Карт"}, {Language::EN, "Cards"}}},
        
        // Account management
        {"create_account", {{Language::RU, "Создать счет"}, {Language::EN, "Create Account"}}},
        {"my_accounts", {{Language::RU, "Мои счета"}, {Language::EN, "My Accounts"}}},
        {"create_card", {{Language::RU, "Создать карту"}, {Language::EN, "Create Card"}}},
        {"back", {{Language::RU, "Назад"}, {Language::EN, "Back"}}},
        {"choose_currency", {{Language::RU, "Выберите валюту (1-RUB, 2-USD, 3-EUR): "}, {Language::EN, "Choose currency (1-RUB, 2-USD, 3-EUR): "}}},
        {"default_currency", {{Language::RU, "Используется RUB по умолчанию"}, {Language::EN, "Using RUB as default"}}},
        {"account_created", {{Language::RU, "Счет создан! Номер: "}, {Language::EN, "Account created! Number: "}}},
        {"account_error", {{Language::RU, "Ошибка создания счета!"}, {Language::EN, "Account creation error!"}}},
        {"no_accounts", {{Language::RU, "Счетов нет"}, {Language::EN, "No accounts"}}},
        {"account_number", {{Language::RU, "Номер"}, {Language::EN, "Number"}}},
        {"balance", {{Language::RU, "Баланс"}, {Language::EN, "Balance"}}},
        {"status", {{Language::RU, "Статус"}, {Language::EN, "Status"}}},
        {"active", {{Language::RU, "Активен"}, {Language::EN, "Active"}}},
        {"inactive", {{Language::RU, "Неактивен"}, {Language::EN, "Inactive"}}},
        {"choose_account", {{Language::RU, "Выберите счет:"}, {Language::EN, "Choose account:"}}},
        {"card_holder_name", {{Language::RU, "Имя держателя карты: "}, {Language::EN, "Card holder name: "}}},
        {"card_created", {{Language::RU, "Карта создана! Номер: "}, {Language::EN, "Card created! Number: "}}},
        {"card_error", {{Language::RU, "Ошибка создания карты!"}, {Language::EN, "Card creation error!"}}},
        {"create_account_first", {{Language::RU, "Сначала создайте счет!"}, {Language::EN, "Create an account first!"}}},
        
        // Operations
        {"deposit", {{Language::RU, "Пополнить счет"}, {Language::EN, "Deposit"}}},
        {"withdraw", {{Language::RU, "Снять средства"}, {Language::EN, "Withdraw"}}},
        {"transfer", {{Language::RU, "Перевод"}, {Language::EN, "Transfer"}}},
        {"amount", {{Language::RU, "Сумма"}, {Language::EN, "Amount"}}},
        {"deposit_success", {{Language::RU, "Счет пополнен успешно!"}, {Language::EN, "Deposit successful!"}}},
        {"deposit_error", {{Language::RU, "Ошибка пополнения счета!"}, {Language::EN, "Deposit error!"}}},
        {"withdraw_success", {{Language::RU, "Средства сняты успешно!"}, {Language::EN, "Withdrawal successful!"}}},
        {"withdraw_error", {{Language::RU, "Ошибка снятия средств! Проверьте баланс и статус счета."}, {Language::EN, "Withdrawal error! Check balance and account status."}}},
        {"choose_withdrawal_account", {{Language::RU, "Выберите счет для списания: "}, {Language::EN, "Choose account to withdraw from: "}}},
        {"recipient_account", {{Language::RU, "Номер счета получателя: "}, {Language::EN, "Recipient account number: "}}},
        {"transfer_success", {{Language::RU, "Перевод выполнен успешно!"}, {Language::EN, "Transfer successful!"}}},
        {"transfer_error", {{Language::RU, "Ошибка перевода! Проверьте баланс и статусы счетов."}, {Language::EN, "Transfer error! Check balances and account statuses."}}},
        {"account_not_found", {{Language::RU, "Счет получателя не найден!"}, {Language::EN, "Recipient account not found!"}}},
        
        // Credit requests
        {"submit_credit_request", {{Language::RU, "Подать заявку на кредит"}, {Language::EN, "Submit Credit Request"}}},
        {"credit_amount", {{Language::RU, "Сумма кредита: "}, {Language::EN, "Credit amount: "}}},
        {"term_months", {{Language::RU, "Срок (месяцев): "}, {Language::EN, "Term (months): "}}},
        {"monthly_payment", {{Language::RU, "Ежемесячный платеж: "}, {Language::EN, "Monthly payment: "}}},
        {"request_submitted", {{Language::RU, "Заявка подана!"}, {Language::EN, "Request submitted!"}}},
        {"request_error", {{Language::RU, "Ошибка подачи заявки!"}, {Language::EN, "Request submission error!"}}},
        
        // Profile
        {"profile_info", {{Language::RU, "Информация о профиле"}, {Language::EN, "Profile Information"}}},
        {"change_password", {{Language::RU, "Сменить пароль"}, {Language::EN, "Change Password"}}},
        {"update_profile", {{Language::RU, "Обновить профиль"}, {Language::EN, "Update Profile"}}},
        {"first_name", {{Language::RU, "Имя"}, {Language::EN, "First Name"}}},
        {"last_name", {{Language::RU, "Фамилия"}, {Language::EN, "Last Name"}}},
        {"phone", {{Language::RU, "Телефон"}, {Language::EN, "Phone"}}},
        {"credit_rating", {{Language::RU, "Кредитный рейтинг"}, {Language::EN, "Credit Rating"}}},
        {"blocked", {{Language::RU, "Заблокирован"}, {Language::EN, "Blocked"}}},
        {"old_password", {{Language::RU, "Старый пароль: "}, {Language::EN, "Old password: "}}},
        {"new_password", {{Language::RU, "Новый пароль: "}, {Language::EN, "New password: "}}},
        {"password_changed", {{Language::RU, "Пароль изменен успешно!"}, {Language::EN, "Password changed successfully!"}}},
        {"password_error", {{Language::RU, "Ошибка смены пароля!"}, {Language::EN, "Password change error!"}}},
        {"profile_updated", {{Language::RU, "Профиль обновлен!"}, {Language::EN, "Profile updated!"}}},
        
        // Common
        {"choose_action", {{Language::RU, "Выберите действие: "}, {Language::EN, "Choose action: "}}},
        {"invalid_choice", {{Language::RU, "Неверный выбор!"}, {Language::EN, "Invalid choice!"}}},
        {"goodbye", {{Language::RU, "До свидания!"}, {Language::EN, "Goodbye!"}}},
        {"critical_error", {{Language::RU, "Критическая ошибка: "}, {Language::EN, "Critical error: "}}},
        {"language_setting", {{Language::RU, "Настройки языка"}, {Language::EN, "Language Settings"}}},
        {"current_language", {{Language::RU, "Текущий язык: "}, {Language::EN, "Current language: "}}},
        {"russian", {{Language::RU, "Русский"}, {Language::EN, "Russian"}}},
        {"english", {{Language::RU, "Английский"}, {Language::EN, "English"}}},
        {"language_changed", {{Language::RU, "Язык изменен!"}, {Language::EN, "Language changed!"}}}
    };

public:
    static void setLanguage(Language lang) {
        currentLanguage = lang;
    }
    
    static Language getCurrentLanguage() {
        return currentLanguage;
    }
    
    static std::string translate(const std::string& key) {
        auto it_key = translations.find(key);
        if (it_key != translations.end()) {
            auto it_lang = it_key->second.find(currentLanguage);
            if (it_lang != it_key->second.end()) {
                return it_lang->second;
            }
        }
        return key; // Return key if translation not found
    }
    
    static std::string getLanguageName(Language lang) {
        switch (lang) {
            case Language::RU: return translate("russian");
            case Language::EN: return translate("english");
            default: return "Unknown";
        }
    }
};

// Helper macros for easier translation
#define TR(key) Localization::translate(key)
#define LANG Localization::getCurrentLanguage()

#endif // LOCALIZATION_H