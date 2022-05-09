#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include "sender/sender.h"

// define different types atm messages
struct withdraw {
    std::string account;
    unsigned int amount;
    mutable messaging::sender atm_queue;

    withdraw(std::string const& account_, unsigned amount_, messaging::sender atm_queue_) :
        account(account_), amount(amount_), atm_queue(atm_queue_) {}
};

struct withdraw_ok {};

struct withdraw_denied {};

struct cancel_withdrawal {
    std::string account;
    unsigned int amount;
    cancel_withdrawal(const std::string& account_, unsigned int amount_) :
        account(account_), amount(amount_) {}
};

struct withdrawal_processed {
    std::string account;
    unsigned int amount;
    withdrawal_processed(const std::string& account_, unsigned int amount_) :
        account(account_), amount(amount_) {}
};

struct card_inserted {
    std::string account;
    explicit card_inserted(const std::string& account_) : account(account_) {}
};

struct digit_pressed {
    char digit;
    explicit digit_pressed(char digit_) : digit(digit_) {}
};

struct clear_last_pressed {};

struct eject_card {};

struct withdraw_pressed {
    unsigned int amount;
    explicit withdraw_pressed(unsigned amount_) : amount(amount_) {}
};

struct cancel_pressed {};

struct issue_money {
    unsigned int amount;
    issue_money(unsigned int amount_) : amount(amount_) {}
};

struct verify_pin {
    std::string account;
    std::string pin;
    mutable messaging::sender atm_queue;
    verify_pin(const std::string& account_, const std::string& pin_, messaging::sender atm_queue_) :
        account(account_), pin(pin_), atm_queue(atm_queue_) {}
};

struct pin_verified {};

struct pin_incorrect {};

struct display_enter_pin {};

struct display_enter_card {};

struct display_insufficient_funds {};

struct display_withdrawal_cancelled {};

struct display_pin_incorrect_message {};

struct display_withdrawal_options {};

struct get_balance {
    std::string account;
    mutable messaging::sender atm_queue;
    get_balance(const std::string& account_, messaging::sender atm_queue_) :
        account(account_), atm_queue(atm_queue_) {}
};

struct balance {
    unsigned int amount;
    explicit balance(unsigned amount_) : amount(amount_) {}
};

struct display_balance {
    unsigned int amount;
    explicit display_balance(unsigned amount_) : amount(amount_) {}
};

struct balance_pressed {};

#endif
