#include <iostream>
#include <vector>

#include "In.h"
#include "../SortBase.h"

template<typename T>
class Insertion : public SortBase<T>
{
public:
    void sort(std::vector<T>& a) override
    {
        int N = a.size();
        for (int i = 1; i < N; ++i)
        {
            for (int j = i; j > 0 && a[j] < a[j - 1]; --j)
                std::swap(a[j], a[j - 1]);
        }
    }
};
