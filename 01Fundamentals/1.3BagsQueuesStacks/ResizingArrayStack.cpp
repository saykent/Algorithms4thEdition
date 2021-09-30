#include <iostream>
#include <array>

#include "StdIn.h"

template<typename T>
class ResizingArrayStack
{
public:
    /**
     * Reserve array_[0] for end of the ReverseIterator
     */
    ResizingArrayStack() : size_{0}, capacity_{1}, array_{new T[2]}
    {
    }

    ~ResizingArrayStack()
    {
        delete[] array_;
    }

    [[nodiscard]] bool isEmpty() const { return size_ == 0; }
    [[nodiscard]] int size() { return size_; }
    void push(T& item)
    {
        if (size_ == capacity_)
            resize(2 * capacity_);
        array_[1 + (size_++)] = item;
    }
    T& pop()
    {
        T& item = array_[1 + (--size_)];
        if (size_ > 0 && size_ == capacity_ / 4)
            resize(capacity_ / 2);
        return item;
    }

    template<bool Const>
    class ReverseArrayIterator
    {
        friend class ResizingArrayStack;
        friend class ReverseArrayIterator<!Const>;

        using pointer = std::conditional_t<Const, const T*, T*>;
        using reference = std::conditional_t<Const, const T&, T&>;
    public:
        explicit ReverseArrayIterator(pointer p) : ptr_{p}
        {}

        reference operator*() const { return *ptr_; }

        auto& operator++()
        {
            --ptr_;

            return *this;
        }

        auto operator++(int)
        {
            auto it = *this;
            ++*this;
            return it;
        }

        template<bool R>
        bool operator==(const ReverseArrayIterator<R>& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }

        template<bool R>
        bool operator!=(const ReverseArrayIterator<R>& rhs) const
        {
            return ptr_ != rhs.ptr_;
        }

    private:
        T* ptr_;
    };

    using const_iterator = ReverseArrayIterator<true>;
    using iterator = ReverseArrayIterator<false>;

    iterator begin()
    {
        return iterator{&array_[size_]};
    }

    iterator end()
    {
        return iterator{&array_[0]};
    }

    const_iterator begin() const
    {
        return const_iterator{&array_[size_]};
    }

    const_iterator end() const
    {
        return const_iterator{&array_[0]};
    }

private:
    void resize(int max)
    {
        T* temp = new T[max+1];
        for (int i = 0; i < size_ + 1; ++i)
            temp[i] = array_[i];
        delete[] array_;

        array_ = temp;
        capacity_ = max;
    }


    int size_;
    int capacity_;
    T* array_;
};

/**
 * string for test: to be or not to - be - - that - - - is
 * result: to be not that or be (2 left on stack)
 * @return
 */
int main()
{
    ResizingArrayStack<std::string> s{};

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

    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}