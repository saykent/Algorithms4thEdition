#include <iostream>
#include <vector>

#include "In.h"

template<typename T>
class Selection
{
public:
    bool isSorted(const std::vector<T>& a)
    {
        int N = a.size();
        for (int i = 1; i < N; ++i)
            if (a[i] < a[i - 1]) return false;
        return true;
    }

    void sort(std::vector<T>& a)
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

    void show(const std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); ++i)
            std::cout << a[i] << " ";

        std::cout << std::endl;
    }
};


int main()
{
    Selection<std::string> sorter;
    stdio::In in;
    std::vector<std::string> a = in.readAllStrings();

    sorter.show(a);
    sorter.sort(a);
    if (sorter.isSorted(a))
        std::cout << "Sorted" << std::endl;
    else
        std::cout << "Not Sorted" << std::endl;

    sorter.show(a);
}