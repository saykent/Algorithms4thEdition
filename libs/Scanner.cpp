#include "Scanner.h"

bool Scanner::hasNext()
{
    ensureOpen();
    saveState();
    while (!sourceClosed_)
    {
        if (hasTokenInBuffer())
            return revertState(true);
        readInput();
    }

    bool result = hasTokenInBuffer();
    return revertState(result);
}

bool Scanner::hasTokenInBuffer()
{
    std::smatch matches;
    if (std::regex_search(buffer_.cbegin() + position_, buffer_.cend(), matches, delimStartPattern_))
    {
        position_ += (matches.position(0) + matches.length());
    }

    if ((buffer_.cbegin() + position_) == buffer_.cend())
        return false;

    return true;
}

void Scanner::readInput()
{
    static const std::streamsize maxSize = 2048;

    makeSpace();

    char delimiter = '\n';
    std::string buf(maxSize, '\0');
    if (source_.get(&buf[0], maxSize, delimiter))
    {
        std::streamsize readSize = source_.gcount();
        if (readSize < maxSize - 1)
        {
            buf.resize(source_.gcount());
            buffer_ += buf;
        }
        else
        {
            throw std::runtime_error("Read maxSize: There might be truncated characters.");
        }
        source_.ignore(1, delimiter);

        appendTokenDelimiterToBuffer();
    }

    if (source_.eof())
    {
        sourceClosed_ = true;
    }
}

std::string Scanner::next()
{
    ensureOpen();

    while (true)
    {
        std::string token = getCompleteTokenInBuffer(findAnyPattern_);
        if (!token.empty())
           return token;

        if (!sourceClosed_)
            readInput();
    }
}

std::string Scanner::getCompleteTokenInBuffer(const std::regex& pattern)
{
    std::smatch firstDelimiters;
    if (std::regex_search(buffer_.cbegin() + position_, buffer_.cend(), firstDelimiters, delimStartPattern_))
    {
        position_ += (firstDelimiters.position(0) + firstDelimiters.length());
        if ((buffer_.cbegin() + position_) == buffer_.cend())
        {
            return "";
        }
    }

    std::smatch nextDelimiters;
    auto nextDelimiterStart = buffer_.cend();
    if (std::regex_search(buffer_.cbegin() + position_, buffer_.cend(), nextDelimiters, delimPattern_))
    {
        nextDelimiterStart = buffer_.cbegin() + position_ + nextDelimiters.position(0);
    }

    std::smatch matches;
    if (std::regex_search(buffer_.cbegin() + position_, nextDelimiterStart, matches, pattern))
    {
        position_ = nextDelimiterStart - buffer_.cbegin();
        return matches[0].str();
    }

    return "";
}
