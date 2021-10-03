#ifndef IN_H
#define IN_H
#include "Scanner.h"

namespace stdio
{
class In
{
public:
    In() : scanner{new Scanner()} {}
    explicit In(std::string name)
    {
        scanner = new Scanner();
    }

    ~In()
    {
        delete scanner;
    }

    bool isEmpty()
    {
        return !scanner->hasNext();
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

private:
    Scanner* scanner;
};
}

#endif //IN_H