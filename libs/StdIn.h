#ifndef STDIN_H
#define STDIN_H

#include "Scanner.h"

class StdIn
{
public:
    static bool isEmpty();

    static std::string readString();

private:
    static stdio::Scanner scanner;
};



#endif //STDIN_H
