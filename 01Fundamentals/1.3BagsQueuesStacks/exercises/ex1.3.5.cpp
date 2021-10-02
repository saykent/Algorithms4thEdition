#include <iostream>
#include "../Stack.h"

int main()
{
    Stack<int> stack;
    int N = 50;
    while (N > 0)
    {
        stack.push(N % 2);
        N = N / 2;
    }

    for (auto& i : stack)
        std::cout << i;
    std::cout << std::endl;
}