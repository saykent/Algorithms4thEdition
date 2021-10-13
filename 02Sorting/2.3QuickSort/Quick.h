#ifndef ALGORITHMS4THEDITION_QUICK_H
#define ALGORITHMS4THEDITION_QUICK_H

#include <random>
#include <algorithm>

#include "../SortBase.h"

template<typename T>
class Quick : public SortBase<T>
{
public:
    void sort(std::vector<T>& a) override
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(a.begin(), a.end(), g);

        sort(a, 0, a.size() - 1);
    }

private:
    void sort(std::vector<T>&a, int lo, int hi)
    {
        if (hi <= lo) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j+1, hi);
    }

    int partition(std::vector<T>& a, int lo, int hi)
    {
        int i = lo, j = hi + 1;
        T v = a[lo];

        while (true)
        {
            while (a[++i] < v) if (i == hi) break;
            while (v < a[--j]) if (j == lo) break;
            if (i >= j) break;

            std::swap(a[i], a[j]);
        }
        std::swap(a[lo], a[j]);

        return j;
    }
};


#endif //ALGORITHMS4THEDITION_QUICK_H
