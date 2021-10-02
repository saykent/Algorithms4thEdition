#include <iostream>
#include <sstream>
#include "StdIn.h"
#include "../Stack.h"

/**
 * input : ( ( 1 + 2 ) * ( ( 3 - 4 ) * ( 5 - 6 ) ) )
 * output: ( ( 1 2 + ) ( ( 3 4 - ) ( 5 6 - ) * ) * )
 * @return
 */
int main()
{
    Stack<std::string> stack;

    while (!StdIn::isEmpty())
    {
        std::string s = StdIn::readString();
        if (s != ")")
            stack.push(s);
        else
        {
            std::string operand2 = stack.pop();
            std::string opr = stack.pop();
            std::string operand1 = stack.pop();
            std::string parenthesis = stack.pop();

            std::ostringstream os;
            os << parenthesis << " " << operand1 << " " << operand2 << " " << opr << " )";
            stack.push(os.str());
        }
    }

    for (auto& item : stack)
        std::cout << item << " ";
    std::cout << std::endl;
}