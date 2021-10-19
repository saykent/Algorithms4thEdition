#include "In.h"
#include "IndexMinPQ.h"

void merge(std::vector<stdio::In*>& streams)
{
    size_t N = streams.size();
    IndexMinPQ<std::string> pq(N);

    for (int i = 0; i < N; ++i)
    {
        if (!streams[i]->isEmpty())
            pq.insert(i, streams[i]->readString());
    }

    while (!pq.isEmpty())
    {
        std::cout << pq.min() << " ";
        int i = pq.delMin();
        if (!streams[i]->isEmpty())
            pq.insert(i, streams[i]->readString());
    }
    std::cout << std::endl;
}
int main(int argc, char *argv[])
{
    int N = argc - 1;
    std::vector<stdio::In*> streams;

    for (int i = 0; i < N; ++i)
    {
       auto in = new stdio::In{argv[i+1]};
       streams.push_back(in);
    }

    merge(streams);
}
