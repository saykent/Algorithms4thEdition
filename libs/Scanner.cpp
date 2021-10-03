#include "Scanner.h"

namespace stdio {
bool Scanner::hasNext()
{
    ensureOpen();
    //saveState();
    while (!sourceClosed_)
    {
        if (hasTokenInBuffer())
            return true;
            //return revertState(true);
        readInput();
    }

    bool result = hasTokenInBuffer();
    return result;
    //return revertState(result);
}

bool Scanner::hasTokenInBuffer()
{
    long searchStartPosition = position_;

    std::smatch matches;
    if (std::regex_search(buffer_.cbegin() + searchStartPosition, buffer_.cend(), matches, delimStartPattern_))
    {
        searchStartPosition += (matches.position(0) + matches.length());
    }

    if ((buffer_.cbegin() + searchStartPosition) == buffer_.cend())
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

std::string Scanner::next(const std::regex& pattern)
{
    ensureOpen();

    while (true)
    {
        std::string token = getCompleteTokenInBuffer(pattern);
        if (!token.empty())
        {
            return token;
        }

        if (!sourceClosed_)
            readInput();
    }
}

int Scanner::nextInt()
{
    try
    {
        std::string s = next(integerPattern_);
        int value = std::stoi(s);
        return value;
    }
    catch (std::out_of_range& e)
    {
        setPositionToPreviousPosition();
        throw std::runtime_error("Exception : " + std::string(e.what()));
    }
    catch (std::invalid_argument& e)
    {
        setPositionToPreviousPosition();
        throw std::runtime_error("Exception : " + std::string(e.what()));
    }
    catch (...)
    {
        setPositionToPreviousPosition();
        throw std::runtime_error("Exception : Unknown");
    }
}

std::string Scanner::getCompleteTokenInBuffer(const std::regex& pattern)
{
    if (buffer_.empty()) return "";

    long searchStartPosition = position_;

    std::smatch firstDelimiters;
    if (std::regex_search(buffer_.cbegin() + searchStartPosition, buffer_.cend(), firstDelimiters, delimStartPattern_))
    {
        searchStartPosition += (firstDelimiters.position(0) + firstDelimiters.length());
        if ((buffer_.cbegin() + searchStartPosition) == buffer_.cend())
        {
            return "";
        }
    }

    std::smatch nextDelimiters;
    auto nextDelimiterStart = buffer_.cend();
    if (std::regex_search(buffer_.cbegin() + searchStartPosition, buffer_.cend(), nextDelimiters, delimPattern_))
    {
        nextDelimiterStart = buffer_.cbegin() + searchStartPosition + nextDelimiters.position(0);
    }

    std::smatch matches;
    if (std::regex_search(buffer_.cbegin() + searchStartPosition, nextDelimiterStart, matches, pattern))
    {
        long position = nextDelimiterStart - buffer_.cbegin();
        setPosition(position);
        return matches[0].str();
    }

    throw InputMismatchException("Failed to find the pattern.");
}

}