#include <iostream>
#include "StdIn.h"
#include "../Stack.h"

/**
 * input : [ ( ) ] { } { [ ( ) ( ) ] ( ) }
 * input : [ ( ) ] { } { [ ( ) ( ) ] ( ] }
 * @return
 */
int main()
{
    Stack<std::string> s{};

    bool result = true;
    while (!StdIn::isEmpty())
    {
        std::string item = StdIn::readString();
        if (item == "[" || item == "(" || item == "{")
            s.push(item);
        else
        {
            std::string popped = s.pop();
            if ((item == "]" && popped == "[")
                ||(item == ")" && popped == "(")
                || (item == "}" && popped == "{"))
            {
            }
            else
            {
                result = false;
                break;
            }
        }
    }
    std::cout << "Result is " << (result ? "true" : "false") << std::endl;
}