#include "In.h"
#include "MinPQ.h"
#include "Transaction.h"
#include "../../01Fundamentals/1.3BagsQueuesStacks/Stack.h"

int main(int argc, char* argv[])
{
    stdio::In in;

    int M = std::atoi(argv[1]);
    MinPQ<Transaction> pq{M+1};

    while (in.hasNextLine())
    {
        pq.insert(Transaction{in.readLine()});
        if (pq.size() > M)
            pq.delMin();
    }

    Stack<Transaction> stack;
    while (!pq.isEmpty()) stack.push(pq.delMin());

    for (auto t : stack)
        std::cout << t << std::endl;
}
