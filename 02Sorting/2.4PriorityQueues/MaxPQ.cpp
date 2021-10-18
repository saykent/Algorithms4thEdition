#include "In.h"
#include "MaxPQ.h"
#include "Transaction.h"
#include "../../01Fundamentals/1.3BagsQueuesStacks/Stack.h"

int main(int argc, char* argv[])
{
    stdio::In in;

    int M = std::atoi(argv[1]);
    MaxPQ<Transaction> pq{M+1};

    while (in.hasNextLine())
    {
        pq.insert(Transaction{in.readLine()});
        if (pq.size() > M)
            pq.delMax();
    }

    Stack<Transaction> stack;
    while (!pq.isEmpty()) stack.push(pq.delMax());

    for (auto t : stack)
        std::cout << t << std::endl;
}
