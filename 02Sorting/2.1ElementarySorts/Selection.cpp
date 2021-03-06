#include <iostream>
#include <vector>

#include "In.h"
#include "Selection.h"

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