
#include "In.h"
#include "Shell.h"


int main()
{
    stdio::In in;
    std::vector<std::string> a = in.readAllStrings();

    Shell<std::string> sorter;
    sorter.show(a);
    sorter.sort(a);
    if (sorter.isSorted(a))
        std::cout << "Sorted" << std::endl;
    else
        std::cout << "Not Sorted" << std::endl;

    sorter.show(a);
}
