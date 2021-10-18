#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <regex>
#include <utility>

namespace stdio {

class InputMismatchException : public std::exception
{
public:
    explicit InputMismatchException(std::string message) : message_{std::move(message)} {}
    std::string what() { return message_; }

private:
    std::string message_;
};

class Scanner
{
private:
    const std::string WHITESPACE_PATTERN{"\\s+"};
    const std::string LINE_SEPARATOR_PATTERN{"\r\n|[\r\n]"};
    const std::string LINE_PATTERN{".*(" + LINE_SEPARATOR_PATTERN + ")|.+$"};

public:
    Scanner() : Scanner{std::cin}
    {}

    Scanner(std::istream& in) : source_{in}, position_{0}, previousPosition_{0}, closed_{false}, sourceClosed_{false},
                                buffer_{}
    {
        delimPattern_ = std::regex{WHITESPACE_PATTERN};
        delimStartPattern_ = std::regex{"^" + WHITESPACE_PATTERN};
        findAnyPattern_ = std::regex{".*"};
        integerPattern_ = std::regex {"[+-]?[[:digit:]]+"};
        linePattern_ = std::regex{LINE_PATTERN};
    }

    bool hasNext();
    bool hasNextLine();
    std::string next();
    std::string next(const std::regex& pattern);
    std::string nextAll();
    int nextInt();
    std::string nextLine();
    std::string findWithinHorizon(const std::regex& pattern, long horizon);
private:
    void ensureOpen()
    {
        if (closed_)
            throw std::runtime_error("Scanner closed");
    }

    void setPosition(long position)
    {
        previousPosition_ = position_;
        position_ = position;
    }

    long getPosition()
    {
        return position_;
    }

    void setPositionToPreviousPosition()
    {
        position_ = previousPosition_;
    }

    bool hasTokenInBuffer();
    bool hasTokenInBuffer(const std::regex& pattern);
    bool hasPatternInBuffer(const std::regex& pattern);

    std::string getCompleteTokenInBuffer(const std::regex& pattern);
    std::string findPatternInBuffer(const std::regex& pattern, long horizon);

    void readInput();

    std::regex& integerPattern()
    {
        return integerPattern_;
    }

    std::regex& linePattern()
    {
        return linePattern_;
    }

    bool makeSpace()
    {
        long offset = position_;
        buffer_.erase(buffer_.begin(), buffer_.begin() + offset);
        position_ -= offset;

        return true;
    }

    void appendTokenDelimiterToBuffer()
    {
        buffer_ += tokenDelimiter_;
    }

private:
    std::string buffer_;
    std::istream& source_;

    bool sourceClosed_;
    bool closed_;

    std::regex delimPattern_;
    std::regex delimStartPattern_;
    std::regex findAnyPattern_;
    std::regex integerPattern_;
    std::regex linePattern_;

    long position_;
    long previousPosition_;
    //long savedScannerPosition_;
    //bool skipped_;

    const std::string tokenDelimiter_{" "};
};
}

#endif //SCANNER_H
