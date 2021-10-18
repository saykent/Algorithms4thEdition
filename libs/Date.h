#ifndef ALGORITHMS4THEDITION_DATE_H
#define ALGORITHMS4THEDITION_DATE_H

#include <iostream>

class Date
{
public:
    Date() = default;
    Date(int month, int day, int year): month_{month}, day_{day}, year_{year} {}
    Date(std::string date)
    {
        if (date.empty())
            throw std::runtime_error("empty string");

        std::string::size_type start = 0;
        std::string::size_type end = date.find('/', start);
        if (end != std::string::npos)
        {
            std::string month = date.substr(start, end - start);
            month_ = std::atoi(month.c_str());
            start = end + 1;
        }
        else
            throw std::runtime_error("Failed to find month");

        end = date.find('/', start);
        if (end != std::string::npos)
        {
            std::string day = date.substr(start, end - start);
            day_ = std::atoi(day.c_str());
            start = end + 1;
        }
        else
            throw std::runtime_error("Failed to find month");

        std::string year = date.substr(start);
        year_ = std::atoi(year.c_str());
    }

    int month() { return month_; }
    int day() { return day_; }
    int year() { return year_; }

    friend std::ostream& operator<<(std::ostream& os, const Date& date)
    {
        os << date.month_ << "/" << date.day_ << "/" << date.year_;
        return os;
    }

private:
    int year_;
    int month_;
    int day_;
};

#endif //ALGORITHMS4THEDITION_DATE_H
