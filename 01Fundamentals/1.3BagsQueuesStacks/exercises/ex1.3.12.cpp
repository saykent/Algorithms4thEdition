#include <iostream>
#include "StdIn.h"
#include "../Stack.h"

Stack<std::string> copyStack(Stack<std::string> stack)
{
    Stack<std::string> tempStack;
    for (auto& item : stack)
        tempStack.push(item);

    Stack<std::string> copiedStack;
    for (auto& item : tempStack)
        copiedStack.push(item);

    return copiedStack;
}

int main()
{
    Stack<std::string> stack;

    while (!StdIn::isEmpty())
    {
        std::string s = StdIn::readString();
        stack.push(s);
    }

    std::cout << "Original stack content: ";
    for (auto& item : stack)
        std::cout << item << " ";
    std::cout << std::endl;

    Stack<std::string> copiedStack = copyStack(stack);
    std::cout << "Copied stack content: ";
    for (auto& item : copiedStack)
        std::cout << item << " ";
    std::cout << std::endl;
}