#include <iostream>
#include "Bag.h"

template<typename T>
void Bag<T>::add(T item)
{
    data_.push_back(item);
}

template<typename T>
bool Bag<T>::isEmpty()
{
    return data_.empty();
}

template<typename T>
int Bag<T>::size()
{
    return data_.size();
}


int main()
{
    Bag<int> bag;

    bag.add(10);
    bag.add(20);

    int sum = 0;
    //for (auto i = bag.begin(); i != bag.end(); ++i)
    for (const auto i : bag)
    {
        sum += i;
    }

    std::cout << "Sum : " << sum << std::endl;
    return EXIT_SUCCESS;
}
