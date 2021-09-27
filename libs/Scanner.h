#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <regex>

class Scanner
{
private:
    const std::string WHITESPACE_PATTERN {"\\s+"};

public:
    Scanner() : Scanner{std::cin}
    {}

    Scanner(std::istream& in) : source_{in}, position_{0}, buffer_{}
    {
        delimPattern_ = std::regex{WHITESPACE_PATTERN};
        delimStartPattern_ = std::regex{"^" + WHITESPACE_PATTERN};
        findAnyPattern_ = std::regex{".*"};
    }

    bool hasNext();

    std::string next();

private:
    void ensureOpen()
    {
        if (closed_)
            throw std::runtime_error("Scanner closed");
    }

    void saveState()
    {
        savedScannerPosition_ = position_;
    }

    bool hasTokenInBuffer();
    std::string getCompleteTokenInBuffer(const std::regex& pattern);

    bool revertState(bool boolResult)
    {
        position_ = savedScannerPosition_;
        savedScannerPosition_ = -1;
        skipped_ = false;
        return boolResult;
    }

    void readInput();

    bool makeSpace()
    {
        long offset = savedScannerPosition_ == -1 ? position_ : savedScannerPosition_;
        buffer_.erase(buffer_.begin(), buffer_.begin() + offset);
        translateSavedIndexes(offset);
        position_ -= offset;

        return true;
    }

    void translateSavedIndexes(long offset)
    {
        if (savedScannerPosition_ != -1)
            savedScannerPosition_ -= offset;
    }

    void appendTokenDelimiterToBuffer()
    {
        buffer_ += tokenDelimiter_;
    }


    std::string buffer_;
    std::istream& source_;

    bool sourceClosed_;
    bool closed_;

    std::regex delimPattern_;
    std::regex delimStartPattern_;
    std::regex findAnyPattern_;

    long position_;
    long savedScannerPosition_;
    bool skipped_;

    const std::string tokenDelimiter_{" "};
};


#endif //SCANNER_H
