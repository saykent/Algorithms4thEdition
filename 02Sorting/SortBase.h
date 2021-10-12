#ifndef ALGORITHMS4THEDITION_SORTBASE_H
#define ALGORITHMS4THEDITION_SORTBASE_H

#include <iostream>
#include <vector>

#include "In.h"

template<typename T>
class SortBase
{
public:
    bool isSorted(const std::vector<T>& a)
    {
        int N = a.size();
        for (int i = 1; i < N; ++i)
            if (a[i] < a[i - 1]) return false;
        return true;
    }

    virtual void sort(std::vector<T>& a) = 0;

    void show(const std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); ++i)
            std::cout << a[i] << " ";

        std::cout << std::endl;
    }
};
#endif //ALGORITHMS4THEDITION_SORTBASE_H
