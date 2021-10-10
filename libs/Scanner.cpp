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

bool Scanner::hasNextLine()
{
    ensureOpen();

    while (!sourceClosed_)
    {
        if (hasPatternInBuffer(linePattern_))
            return true;

        readInput();
    }

    bool result = hasPatternInBuffer(linePattern_);
    return result;
}

bool Scanner::hasTokenInBuffer()
{
    return hasTokenInBuffer(delimStartPattern_);
}

bool Scanner::hasTokenInBuffer(const std::regex& pattern)
{
    long searchStartPosition = position_;

    std::smatch matches;
    if (std::regex_search(buffer_.cbegin() + searchStartPosition, buffer_.cend(), matches, pattern))
    {
        searchStartPosition += (matches.position(0) + matches.length());
    }

    if ((buffer_.cbegin() + searchStartPosition) == buffer_.cend())
        return false;

    return true;
}

bool Scanner::hasPatternInBuffer(const std::regex& pattern)
{
    long searchStartPosition = position_;

    std::smatch matches;
    if (std::regex_search(buffer_.cbegin() + searchStartPosition, buffer_.cend(), matches, pattern))
    {
        return true;
    }

    return false;
}

void Scanner::readInput()
{
    static const std::streamsize maxSize = 2048;

    makeSpace();

    while (true)
    {
        std::string buf(maxSize, '\0');
        if (source_.getline(&buf[0], maxSize))
        {
            buf.resize(source_.gcount() - 1); // remove  '\0'
            buffer_ += buf;

            appendTokenDelimiterToBuffer();
        }

        if (source_.eof())
        {
            sourceClosed_ = true;
            break;
        }
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

std::string Scanner::nextAll()
{
    return findPatternInBuffer(findAnyPattern_, 0);
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

std::string Scanner::findWithinHorizon(const std::regex& pattern, long horizon)
{
    while (true)
    {
        std::string token = findWithinHorizon(pattern, horizon);
        if (!token.empty())
            return token;

        if (!sourceClosed_)
            readInput();
        else
            break;
    }
    return std::string{};
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

std::string Scanner::findPatternInBuffer(const std::regex& pattern, long horizon)
{
    auto searchLimit = buffer_.cend();
    if (horizon > 0)
    {
        long horizonMax = buffer_.cend() - (buffer_.cbegin() + position_);
        if (horizon < horizonMax)
            searchLimit = buffer_.cbegin() + position_ + horizon;
    }

    std::smatch matches;
    if (std::regex_search(buffer_.cbegin() + position_, searchLimit, matches, pattern))
    {
        long position = position_ + matches.position(0) + matches.length(0);
        setPosition(position);

        return matches[0].str();
    }

    return "";
}

}