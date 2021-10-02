#include <iostream>
#include <sstream>
#include "StdIn.h"
#include "../Stack.h"

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

            std::ostringstream os;
            os << "( " << operand1 << " " << opr << " " << operand2 << " )";
            stack.push(os.str());
        }
    }

    for (auto& item : stack)
        std::cout << item << " ";
    std::cout << std::endl;
}