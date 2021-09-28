#include <iostream>
#include <array>

#include "StdIn.h"

class FixedCapacityStackOfStrings
{
public:
    FixedCapacityStackOfStrings(int capacity) : size_{0}, array_{new std::string[capacity]}
    {
    }

    ~FixedCapacityStackOfStrings()
    {
        delete[] array_;
    }

    [[nodiscard]] bool isEmpty() const { return size_ == 0; }
    [[nodiscard]] int size() { return size_; }
    void push(std::string& item) { array_[size_++] = item; }
    std::string& pop() { return array_[--size_]; }

private:
    int size_;
    std::string* array_;
};

int main()
{
    FixedCapacityStackOfStrings s(100);

    while (!StdIn::isEmpty())
    {
        std::string item = StdIn::readString();
        if (item != "-")
            s.push(item);
        else if (!s.isEmpty())
        {
            std::cout << s.pop() << " ";
        }
    }
    std::cout << "(" << s.size() << " left on stack)" << std::endl;
}