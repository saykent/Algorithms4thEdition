#ifndef ALGORITHMS4THEDITION_MERGE_H
#define ALGORITHMS4THEDITION_MERGE_H

#include "../SortBase.h"

template<typename T>
class Merge : public SortBase<T>
{
public:
    void sort(std::vector<T>& a) override
    {
        aux_.resize(a.size());
        sort(a, 0, a.size() - 1);
    }

private:
    void sort(std::vector<T>& a, int lo, int hi)
    {
        if (hi <= lo) return;

        int mid = lo + (hi - lo) / 2;
        sort(a, lo, mid);
        sort(a, mid+1, hi);
        merge(a, lo, mid, hi);
    }

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


#endif //ALGORITHMS4THEDITION_MERGE_H
