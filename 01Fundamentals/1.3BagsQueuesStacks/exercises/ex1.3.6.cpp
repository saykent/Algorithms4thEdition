#include <iostream>
#include "StdIn.h"
#include "../Stack.h"
#include "../Queue.h"

int main()
{
    Queue<std::string> q;
    std::cout << "Enter a string: ";
    while (!StdIn::isEmpty())
    {
        std::string s = StdIn::readString();
        q.enqueue(s);
    }
    std::cout << "Content in the queue : ";
    for (auto& item : q)
        std::cout << item << " ";
    std::cout << std::endl;

   Stack<std::string> stack;
    while (!q.isEmpty())
        stack.push(q.dequeue());
    while (!stack.isEmpty())
        q.enqueue(stack.pop());
    std::cout << "Content in the queue : ";
    for (auto& item : q)
        std::cout << item << " ";
    std::cout << std::endl;
}
