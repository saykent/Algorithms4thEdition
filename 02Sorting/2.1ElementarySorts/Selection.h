#include <iostream>
#include <vector>

#include "In.h"
#include "SortBase.h"

template<typename T>
class Selection : public SortBase<T>
{
public:
    void sort(std::vector<T>& a) override
    {
        int N = a.size();
        for (int i = 0; i < N; ++i)
        {
            int min = i;
            for (int j = i + 1; j < N; ++j)
            {
                if (a[j] < a[min]) min = j;
            }
            std::swap(a[i], a[min]);
        }
    }
};
