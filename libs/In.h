#ifndef IN_H
#define IN_H

#include <regex>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "Scanner.h"

namespace stdio
{
class In
{
public:
    In() : scanner{new Scanner()} {}
    explicit In(const std::string& name)
    {
        filestream_.open(name);
        if (filestream_.is_open())
            scanner = new Scanner(filestream_);
        else
            throw std::runtime_error("Failed to open the file.");
    }

    ~In()
    {
        delete scanner;
        filestream_.close();
    }

    bool isEmpty()
    {
        return !scanner->hasNext();
    }

    bool hasNextLine()
    {
        return scanner->hasNextLine();
    }

    std::string readString()
    {
        return scanner->next();
    }

    int readInt()
    {
        try
        {
            return scanner->nextInt();
        }
        catch (...)
        {
            std::string token = scanner->next();
            throw std::runtime_error("Cannot get integer value. The token was " + token);
        }
    }

    std::string readLine()
    {
        try
        {
            return scanner->nextLine();
        }
        catch (...)
        {
            std::string token = scanner->next();
            throw std::runtime_error("Cannot get integer value. The token was " + token);
        }
    }

    std::string readAll()
    {
        if (!scanner->hasNextLine())
            return "";

        return scanner->nextAll();
    }

    std::vector<std::string> readAllStrings()
    {
        std::vector<std::string> tokens = split(readAll());
        //std::vector<std::string> tokens = split(readAll(), ' ');

        return tokens;
    }

private:
    template<typename Out>
    void split(const std::string& s, char delim, Out result)
    {
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delim))
        {
            *result++ = item;
        }
    }

    std::vector<std::string> split(const std::string& s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));

        return elems;
    }

    std::vector<std::string> split(const std::string& s)
    {
        std::regex pattern{"\\s+|\r\n|[\r\n]"};
        return split(s, pattern);
    }

    std::vector<std::string> split(const std::string& str, const std::regex& pattern)
    {
        return std::vector<std::string> {std::sregex_token_iterator(str.begin(), str.end(), pattern, -1), std::sregex_token_iterator()};
    }


private:
    Scanner* scanner;
    std::ifstream filestream_;
};
}

#endif //IN_H