#ifndef ALGORITHMS4THEDITION_MAXPQ_H
#define ALGORITHMS4THEDITION_MAXPQ_H

#include <iostream>
#include <vector>

template<typename T>
class MaxPQ
{
public:
    MaxPQ(int maxN) : N{0}
    {
        pq.resize(maxN + 1);
    }

    bool isEmpty() { return N == 0; }
    int size() { return N;}

    void insert(T v)
    {
        pq[++N] = v;
        swim(N);
    }

    T delMax()
    {
        T max = pq[1];
        exch(1, N--);
        sink(1);

        return max;
    }

private:
    void swim(int k)
    {
        while (k > 1 && less(k/2, k))
        {
            exch(k / 2, k);
            k = k / 2;
        }

    }

    void sink(int k)
    {
        while (2*k <= N)
        {
            int j = 2*k;
            if (j < N && less(j, j + 1)) ++j;
            if (!less(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

    void exch(int i, int j)
    {
        std::swap(pq[i], pq[j]);
    }

    bool less(int i, int j)
    {
        return pq[i] < pq[j];
    }

private:
    std::vector<T> pq;
    int N;
};


#endif //ALGORITHMS4THEDITION_MAXPQ_H
