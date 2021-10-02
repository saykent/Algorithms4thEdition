#include <iostream>
#include "StdIn.h"
#include "../ResizingArrayStack.h"

int main()
{
    ResizingArrayStack<std::string> stack;
    while (!StdIn::isEmpty())
    {
        std::string s = StdIn::readString();
        if (s != "-")
            stack.push(s);
        else if (!stack.isEmpty())
            stack.pop();
    }

    std::cout << "Content in the stack: ";
    for (auto& item : stack)
        std::cout << item << " ";
    std::cout << std::endl;

    std::cout << "Size of the stack: " << stack.size() << std::endl;
}