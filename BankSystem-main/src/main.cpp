// main.cpp
#include "../include/bank_system.h"
#include "localization.h"
#include <iostream>
#include <limits>
#include <iomanip>

class BankConsoleApp {
private:
    BankSystem bank;
    std::shared_ptr<User> currentUser;

public:
    void run() {
        showLanguageSelection();
        
        while (true) {
            showMainMenu();
        }
    }

private:
    void showLanguageSelection() {
        std::cout << "\n=================================\n";
        std::cout << "        LANGUAGE SELECTION\n";
        std::cout << "        ВЫБОР ЯЗЫКА\n";
        std::cout << "=================================\n";
        std::cout << "1. English\n";
        std::cout << "2. Русский\n";
        std::cout << "Choose language / Выберите язык: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: Localization::setLanguage(Language::EN); break;
            case 2: Localization::setLanguage(Language::RU); break;
            default: Localization::setLanguage(Language::EN); break;
        }
    }

    void showMainMenu() {
        std::cout << "\n=================================\n";
        std::cout << "      " << TR("bank_system") << "\n";
        std::cout << "=================================\n";
        
        if (!currentUser) {
            std::cout << "1. " << TR("registration") << "\n";
            std::cout << "2. " << TR("login") << "\n";
            std::cout << "3. " << TR("system_stats") << "\n";
            std::cout << "4. " << TR("language_setting") << "\n";
            std::cout << "5. " << TR("exit") << "\n";
        } else {
            std::cout << TR("welcome") << currentUser->getUsername() << "!\n";
            std::cout << "1. " << TR("account_management") << "\n";
            std::cout << "2. " << TR("operations") << "\n";
            std::cout << "3. " << TR("credit_requests") << "\n";
            std::cout << "4. " << TR("profile") << "\n";
            std::cout << "5. " << TR("language_setting") << "\n";
            std::cout << "6. " << TR("logout") << "\n";
        }
        
        std::cout << TR("choose_action");
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (!currentUser) {
            handleUnauthenticatedMenu(choice);
        } else {
            handleAuthenticatedMenu(choice);
        }
    }

    void handleUnauthenticatedMenu(int choice) {
        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: showSystemStats(); break;
            case 4: changeLanguage(); break;
            case 5: exitApp(); break;
            default: std::cout << TR("invalid_choice") << "\n";
        }
    }

    void handleAuthenticatedMenu(int choice) {
        switch (choice) {
            case 1: manageAccounts(); break;
            case 2: performOperations(); break;
            case 3: manageCreditRequests(); break;
            case 4: manageProfile(); break;
            case 5: changeLanguage(); break;
            case 6: logoutUser(); break;
            default: std::cout << TR("invalid_choice") << "\n";
        }
    }

    void changeLanguage() {
        std::cout << "\n--- " << TR("language_setting") << " ---\n";
        std::cout << TR("current_language") << Localization::getLanguageName(LANG) << "\n";
        std::cout << "1. English\n";
        std::cout << "2. Русский\n";
        std::cout << TR("choose_action");
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: Localization::setLanguage(Language::EN); break;
            case 2: Localization::setLanguage(Language::RU); break;
            default: std::cout << TR("invalid_choice") << "\n"; return;
        }
        
        std::cout << TR("language_changed") << "\n";
    }

    void registerUser() {
        std::string username, email, password;
        
        std::cout << "\n--- " << TR("registration") << " ---\n";
        std::cout << TR("username") << ": ";
        std::getline(std::cin, username);
        
        std::cout << TR("email") << ": ";
        std::getline(std::cin, email);
        
        std::cout << TR("password") << ": ";
        std::getline(std::cin, password);
        
        auto user = bank.registerUser(username, email, password);
        if (user) {
            std::cout << TR("registration_success") << user->getId() << "\n";
        } else {
            std::cout << TR("registration_error") << "\n";
        }
    }

    void loginUser() {
        std::string username, password;
        
        std::cout << "\n--- " << TR("login") << " ---\n";
        std::cout << TR("username") << ": ";
        std::getline(std::cin, username);
        
        std::cout << TR("password") << ": ";
        std::getline(std::cin, password);
        
        currentUser = bank.authenticateUser(username, password);
        if (currentUser) {
            std::cout << TR("login_success") << "\n";
        } else {
            std::cout << TR("login_error") << "\n";
        }
    }

    void showSystemStats() {
        std::cout << "\n--- " << TR("system_stats") << " ---\n";
        std::cout << TR("users_count") << ": " << bank.getUsersCount() << "\n";
        std::cout << TR("accounts_count") << ": " << bank.getAccountsCount() << "\n";
        std::cout << TR("cards_count") << ": " << bank.getCardsCount() << "\n";
    }

    void manageAccounts() {
        while (true) {
            std::cout << "\n--- " << TR("account_management") << " ---\n";
            std::cout << "1. " << TR("create_account") << "\n";
            std::cout << "2. " << TR("my_accounts") << "\n";
            std::cout << "3. " << TR("create_card") << "\n";
            std::cout << "4. " << TR("back") << "\n";
            std::cout << TR("choose_action");
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: createAccount(); break;
                case 2: showUserAccounts(); break;
                case 3: createCard(); break;
                case 4: return;
                default: std::cout << TR("invalid_choice") << "\n";
            }
        }
    }

    void createAccount() {
        std::cout << "\n--- " << TR("create_account") << " ---\n";
        std::cout << TR("choose_currency");
        int currencyChoice;
        std::cin >> currencyChoice;
        std::cin.ignore();
        
        Currency currency = Currency::RUB;
        switch (currencyChoice) {
            case 1: currency = Currency::RUB; break;
            case 2: currency = Currency::USD; break;
            case 3: currency = Currency::EUR; break;
            default: std::cout << TR("default_currency") << "\n";
        }
        
        auto account = bank.createAccount(currentUser->getId(), currency);
        if (account) {
            std::cout << TR("account_created") << account->getAccountNumber() << "\n";
        } else {
            std::cout << TR("account_error") << "\n";
        }
    }

    void showUserAccounts() {
        auto accounts = bank.findAccountsByUserId(currentUser->getId());
        std::cout << "\n--- " << TR("my_accounts") << " ---\n";
        
        if (accounts.empty()) {
            std::cout << TR("no_accounts") << "\n";
            return;
        }
        
        for (size_t i = 0; i < accounts.size(); ++i) {
            auto acc = accounts[i];
            std::cout << (i + 1) << ". " << TR("account_number") << ": " << acc->getAccountNumber()
                      << " " << TR("balance") << ": " << std::fixed << std::setprecision(2) << acc->getBalance()
                      << " " << TR("status") << ": " << (acc->isActive() ? TR("active") : TR("inactive")) << "\n";
        }
    }

    void createCard() {
        auto accounts = bank.findAccountsByUserId(currentUser->getId());
        if (accounts.empty()) {
            std::cout << TR("create_account_first") << "\n";
            return;
        }
        
        std::cout << "\n--- " << TR("create_card") << " ---\n";
        std::cout << TR("choose_account") << "\n";
        for (size_t i = 0; i < accounts.size(); ++i) {
            std::cout << (i + 1) << ". " << accounts[i]->getAccountNumber() << "\n";
        }
        
        int accountChoice;
        std::cin >> accountChoice;
        std::cin.ignore();
        
        if (accountChoice < 1 || accountChoice > static_cast<int>(accounts.size())) {
            std::cout << TR("invalid_choice") << "\n";
            return;
        }
        
        std::string holderName;
        std::cout << TR("card_holder_name");
        std::getline(std::cin, holderName);
        
        auto card = bank.createCard(accounts[accountChoice - 1]->getAccountNumber(), holderName);
        if (card) {
            std::cout << TR("card_created") << card->getMaskedCardNumber() << "\n";
        } else {
            std::cout << TR("card_error") << "\n";
        }
    }

    void performOperations() {
        while (true) {
            std::cout << "\n--- " << TR("operations") << " ---\n";
            std::cout << "1. " << TR("deposit") << "\n";
            std::cout << "2. " << TR("withdraw") << "\n";
            std::cout << "3. " << TR("transfer") << "\n";
            std::cout << "4. " << TR("back") << "\n";
            std::cout << TR("choose_action");
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: deposit(); break;
                case 2: withdraw(); break;
                case 3: transfer(); break;
                case 4: return;
                default: std::cout << TR("invalid_choice") << "\n";
            }
        }
    }

    void deposit() {
        auto accounts = bank.findAccountsByUserId(currentUser->getId());
        if (accounts.empty()) {
            std::cout << TR("create_account_first") << "\n";
            return;
        }
        
        std::cout << "\n--- " << TR("deposit") << " ---\n";
        showAccountsList(accounts);
        
        int accountChoice;
        std::cout << TR("choose_account");
        std::cin >> accountChoice;
        
        if (accountChoice < 1 || accountChoice > static_cast<int>(accounts.size())) {
            std::cout << TR("invalid_choice") << "\n";
            return;
        }
        
        double amount;
        std::cout << TR("amount") << ": ";
        std::cin >> amount;
        
        if (accounts[accountChoice - 1]->deposit(amount)) {
            std::cout << TR("deposit_success") << "\n";
        } else {
            std::cout << TR("deposit_error") << "\n";
        }
    }

    void withdraw() {
        auto accounts = bank.findAccountsByUserId(currentUser->getId());
        if (accounts.empty()) {
            std::cout << TR("create_account_first") << "\n";
            return;
        }
        
        std::cout << "\n--- " << TR("withdraw") << " ---\n";
        showAccountsList(accounts);
        
        int accountChoice;
        std::cout << TR("choose_withdrawal_account");
        std::cin >> accountChoice;
        
        if (accountChoice < 1 || accountChoice > static_cast<int>(accounts.size())) {
            std::cout << TR("invalid_choice") << "\n";
            return;
        }
        
        double amount;
        std::cout << TR("amount") << ": ";
        std::cin >> amount;
        
        if (accounts[accountChoice - 1]->withdraw(amount)) {
            std::cout << TR("withdraw_success") << "\n";
        } else {
            std::cout << TR("withdraw_error") << "\n";
        }
    }

    void transfer() {
        auto accounts = bank.findAccountsByUserId(currentUser->getId());
        if (accounts.empty()) {
            std::cout << TR("create_account_first") << "\n";
            return;
        }
        
        std::cout << "\n--- " << TR("transfer") << " ---\n";
        showAccountsList(accounts);
        
        int fromAccountChoice;
        std::cout << TR("choose_withdrawal_account");
        std::cin >> fromAccountChoice;
        
        if (fromAccountChoice < 1 || fromAccountChoice > static_cast<int>(accounts.size())) {
            std::cout << TR("invalid_choice") << "\n";
            return;
        }
        
        std::string toAccountNumber;
        std::cout << TR("recipient_account");
        std::cin >> toAccountNumber;
        
        double amount;
        std::cout << TR("amount") << ": ";
        std::cin >> amount;
        
        auto toAccount = bank.findAccountByNumber(toAccountNumber);
        if (!toAccount) {
            std::cout << TR("account_not_found") << "\n";
            return;
        }
        
        if (accounts[fromAccountChoice - 1]->transfer(toAccount, amount)) {
            std::cout << TR("transfer_success") << "\n";
        } else {
            std::cout << TR("transfer_error") << "\n";
        }
    }

    void manageCreditRequests() {
        while (true) {
            std::cout << "\n--- " << TR("credit_requests") << " ---\n";
            std::cout << "1. " << TR("submit_credit_request") << "\n";
            std::cout << "2. " << TR("back") << "\n";
            std::cout << TR("choose_action");
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: submitCreditRequest(); break;
                case 2: return;
                default: std::cout << TR("invalid_choice") << "\n";
            }
        }
    }

    void submitCreditRequest() {
        std::cout << "\n--- " << TR("submit_credit_request") << " ---\n";
        
        double amount;
        std::cout << TR("credit_amount");
        std::cin >> amount;
        
        int termMonths;
        std::cout << TR("term_months");
        std::cin >> termMonths;
        
        auto request = bank.submitCreditRequest(currentUser->getId(), amount, termMonths);
        if (request) {
            std::cout << TR("request_submitted") << " " << TR("monthly_payment") << request->getMonthlyPayment() << "\n";
        } else {
            std::cout << TR("request_error") << "\n";
        }
    }

    void manageProfile() {
        while (true) {
            std::cout << "\n--- " << TR("profile") << " ---\n";
            std::cout << "1. " << TR("profile_info") << "\n";
            std::cout << "2. " << TR("change_password") << "\n";
            std::cout << "3. " << TR("update_profile") << "\n";
            std::cout << "4. " << TR("back") << "\n";
            std::cout << TR("choose_action");
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: showProfile(); break;
                case 2: changePassword(); break;
                case 3: updateProfile(); break;
                case 4: return;
                default: std::cout << TR("invalid_choice") << "\n";
            }
        }
    }

    void showProfile() {
        std::cout << "\n--- " << TR("profile_info") << " ---\n";
        std::cout << TR("username") << ": " << currentUser->getUsername() << "\n";
        std::cout << TR("email") << ": " << currentUser->getEmail() << "\n";
        std::cout << TR("first_name") << ": " << currentUser->getFirstName() << "\n";
        std::cout << TR("last_name") << ": " << currentUser->getLastName() << "\n";
        std::cout << TR("credit_rating") << ": " << currentUser->getCreditRating() << "\n";
        std::cout << TR("status") << ": " << (currentUser->isActive() ? TR("active") : TR("blocked")) << "\n";
    }

    void changePassword() {
        std::string oldPassword, newPassword;
        
        std::cout << "\n--- " << TR("change_password") << " ---\n";
        std::cout << TR("old_password");
        std::getline(std::cin, oldPassword);
        
        std::cout << TR("new_password");
        std::getline(std::cin, newPassword);
        
        if (currentUser->changePassword(oldPassword, newPassword)) {
            std::cout << TR("password_changed") << "\n";
        } else {
            std::cout << TR("password_error") << "\n";
        }
    }

    void updateProfile() {
        std::string firstName, lastName, phone, email;
        
        std::cout << "\n--- " << TR("update_profile") << " ---\n";
        std::cout << TR("first_name") << ": ";
        std::getline(std::cin, firstName);
        
        std::cout << TR("last_name") << ": ";
        std::getline(std::cin, lastName);
        
        std::cout << TR("phone") << ": ";
        std::getline(std::cin, phone);
        
        std::cout << TR("email") << ": ";
        std::getline(std::cin, email);
        
        currentUser->updateProfile(firstName, lastName, phone, email);
        std::cout << TR("profile_updated") << "\n";
    }

    void showAccountsList(const std::vector<std::shared_ptr<Account>>& accounts) {
        for (size_t i = 0; i < accounts.size(); ++i) {
            std::cout << (i + 1) << ". " << accounts[i]->getAccountNumber() 
                      << " (" << TR("balance") << ": " << std::fixed << std::setprecision(2) << accounts[i]->getBalance() << ")\n";
        }
    }

    void logoutUser() {
        currentUser = nullptr;
        std::cout << TR("logout") << " " << TR("success") << "\n";
    }

    void exitApp() {
        std::cout << TR("goodbye") << "\n";
        exit(0);
    }
};

int main() {
    try {
        BankConsoleApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << TR("critical_error") << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}