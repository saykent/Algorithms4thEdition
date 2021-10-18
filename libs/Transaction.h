#ifndef ALGORITHMS4THEDITION_TRANSACTION_H
#define ALGORITHMS4THEDITION_TRANSACTION_H

#import <iostream>

#include "Date.h"

class Transaction
{
public:
    Transaction() = default;
    Transaction(const std::string& transaction)
    {
        if (transaction.empty())
            throw std::runtime_error("empty string");

        std::string::size_type start = 0;
        std::string::size_type end = transaction.find(' ', start);
        if (end != std::string::npos)
        {
            who_ = transaction.substr(start, end - start);
            start = end + 1;
            while (transaction[start] == ' ') ++start;
        }
        else
            throw std::runtime_error("Failed to find who");

        end = transaction.find(' ', start);
        if (end != std::string::npos)
        {
            std::string date = transaction.substr(start, end - start);
            when_ = Date{date};
            start = end + 1;
            while (transaction[start] == ' ') ++start;
        }
        else
            throw std::runtime_error("Failed to find date");

        std::string amount = transaction.substr(start);
        amount_ = std::atof(amount.c_str());
    }

    Transaction(std::string who, Date when, double amount)
    : who_{std::move(who)}, when_{when}, amount_{amount}
    {

    }

    std::string who() { return who_; }
    Date when() { return when_; }
    double amount() { return amount_; }


    bool operator<(const Transaction& rhs) const
    {
        return this->amount_ < rhs.amount_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction)
    {
        os << transaction.who_ << "\t\t" << transaction.when_ << "\t\t" << transaction.amount_ << std::endl;
        return os;
    }

private:
    std::string who_;
    double amount_;
    Date when_;
};

#endif //ALGORITHMS4THEDITION_TRANSACTION_H
