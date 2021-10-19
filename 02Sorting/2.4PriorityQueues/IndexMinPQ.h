#ifndef ALGORITHMS4THEDITION_INDEXMINPQ_H
#define ALGORITHMS4THEDITION_INDEXMINPQ_H

#include <iostream>
#include <vector>

template<typename T>
class IndexMinPQ
{
public:
    IndexMinPQ(int maxN) : N{0}
    {
        keys.resize(maxN + 1);
        pq.resize(maxN + 1);
        qp.resize(maxN + 1);

        for (int i = 0; i <= maxN; ++i)
            qp[i] = -1;
    }

    bool isEmpty() { return N == 0; }
    int size() { return N;}
    bool contains(int k) { return qp[k] != -1; }

    void insert(int k, T key)
    {
        ++N;
        qp[k] = N;
        pq[N] = k;
        keys[k] = key;
        swim(N);
    }

    T min() { return keys[pq[1]]; }

    int delMin()
    {
        int indexOfMin = pq[1];
        exch(1, N--);
        sink(1);
        qp[pq[N + 1]] = -1;

        return indexOfMin;
    }

    int minIndex() { return pq[1]; }

    void change(int k, T key)
    {
        keys[k] = key;
        swim(qp[k]);
        sink(qp[k]);
    }

    void remove(int k)
    {
        exch(k, N--);
        swim(qp[k]);
        sink(qp[k]);
        qp[pq[N+1]] = -1;
    }

private:
    void swim(int k)
    {
        while (k > 1 && greater(k/2, k))
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
            if (j < N && greater(j, j + 1)) ++j;
            if (!greater(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

    void exch(int i, int j)
    {
        std::swap(qp[pq[i]], qp[pq[j]]);
        std::swap(pq[i], pq[j]);
    }

    bool greater(int i, int j)
    {
        return keys[pq[j]] < keys[pq[i]];
    }

private:
    int N;
    std::vector<int> pq;
    std::vector<int> qp;
    std::vector<T> keys;
};


#endif //ALGORITHMS4THEDITION_INDEXMINPQ_H
