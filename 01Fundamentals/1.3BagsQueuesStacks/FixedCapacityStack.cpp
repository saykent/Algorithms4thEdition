#include <iostream>
#include <array>

#include "StdIn.h"

template<typename T>
class FixedCapacityStack
{
public:
    FixedCapacityStack(int capacity) : size_{0}, array_{new T[capacity]}
    {
    }

    ~FixedCapacityStack()
    {
        delete[] array_;
    }

    [[nodiscard]] bool isEmpty() const { return size_ == 0; }
    [[nodiscard]] int size() { return size_; }
    void push(T& item) { array_[size_++] = item; }
    T& pop() { return array_[--size_]; }

private:
    int size_;
    T* array_;
};

/**
 * string for test: to be or not to - be - - that - - - is
 * result: to be not that or be (2 left on stack)
 * @return
 */
int main()
{
    FixedCapacityStack<std::string> s(100);

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