#include "StdIn.h"

using namespace stdio;

Scanner StdIn::scanner;

bool StdIn::isEmpty()
{
    return !scanner.hasNext();
}

std::string StdIn::readString()
{
    return scanner.next();
}
