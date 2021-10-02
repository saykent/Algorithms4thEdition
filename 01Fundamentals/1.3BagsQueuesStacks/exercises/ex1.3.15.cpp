#include <iostream>
#include "../Queue.h"
#include "StdIn.h"

int main(int argc, char* argv[])
{
    int k = 0;
    if (argc > 1)
        k = atoi(argv[1]);

    Queue<std::string> queue;

    while (!StdIn::isEmpty())
    {
        std::string s = StdIn::readString();
        queue.enqueue(s);
    }

    if (queue.size() >= k)
    {
        int skipCount = queue.size() - k;
        for (int i = 0; i < skipCount; ++i)
            queue.dequeue();

        std::cout << k << "th from the last is : " << queue.dequeue() << std::endl;
    }
    else
    {
        std::cout << "Input string is too short" << std::endl;
    }
}