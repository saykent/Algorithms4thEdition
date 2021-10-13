#include "Quick.h"
#include "In.h"

int main()
{
    Quick<std::string> sorter;
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
