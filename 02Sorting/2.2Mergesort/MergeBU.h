#ifndef ALGORITHMS4THEDITION_MERGEBU_H
#define ALGORITHMS4THEDITION_MERGEBU_H

#include "../SortBase.h"

template<typename T>
class MergeBU : public SortBase<T>
{
public:
    void sort(std::vector<T>& a) override
    {
        int N = a.size();

        aux_.resize(N);
        for (int sz = 1; sz < N; sz = sz + sz)
            for (int lo = 0; lo < N - sz; lo += sz + sz)
                merge(a, lo, lo + sz - 1, std::min(lo+sz+sz-1, N-1));
    }

private:
    void merge(std::vector<T>& a, int lo, int mid, int hi)
    {
        int i = lo, j = mid + 1;

        for (int k = lo; k <= hi; ++k)
            aux_[k] = a[k];

        for (int k = lo; k <= hi; ++k)
        {
            if      (i > mid)               a[k] = aux_[j++];
            else if (j > hi)                a[k] = aux_[i++];
            else if ( aux_[j] < aux_[i])    a[k] = aux_[j++];
            else                            a[k] = aux_[i++];
        }
    }

private:
    std::vector<T> aux_;
};


#endif //ALGORITHMS4THEDITION_MERGEBU_H
