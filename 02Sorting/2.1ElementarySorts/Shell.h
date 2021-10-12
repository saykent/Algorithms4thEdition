#ifndef ALGORITHMS4THEDITION_SHELL_H
#define ALGORITHMS4THEDITION_SHELL_H

#include "../SortBase.h"

template<typename T>
class Shell : public SortBase<T>
{
public:
    void sort(std::vector<T>& a) override
    {
        int N = a.size();
        int h = 1;
        while (h < N/3) h = 3*h + 1;

        while (h >= 1)
        {
            for (int i = h; i < N; ++i)
            {
                for (int j = i; j >= h && a[j] < a[j - h]; j -= h)
                    std::swap(a[j], a[j - h]);
            }

            h = h / 3;
        }

    }

};


#endif //ALGORITHMS4THEDITION_SHELL_H
