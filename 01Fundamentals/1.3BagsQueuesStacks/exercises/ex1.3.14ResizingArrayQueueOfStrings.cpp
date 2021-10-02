#include <iostream>
#include "StdIn.h"

class ResizingArrayOfStrings
{
public:
    ResizingArrayOfStrings() : size_{0}, capacity_{1}, array_{new std::string[1]} {}
    ~ResizingArrayOfStrings() { delete[] array_; }

    bool isEmpty() { return size_ == 0; }
    int size() { return size_; }

    void enqueue(std::string& item)
    {
        if (size_ == capacity_)
            resize(2 * capacity_);
        array_[size_] = item;
        ++size_;
    }

    std::string& dequeue()
    {
        std::string& item = array_[0];
        --size_;
        if (size_ > 0 && size_ == capacity_ / 4)
            resize(capacity_ / 2);
        else
        {
            for (int i = 0; i < size_; ++i)
                array_[i] = array_[i + 1];
        }

        return item;
    }

    template<bool Const>
    class ResizingArrayOfStringIterator
    {
        friend class ResizingArrayOfString;
        friend class ResizingArrayOfStringIterator<!Const>;

        using pointer = std::conditional_t<Const, const std::string*, std::string*>;
        using reference = std::conditional_t<Const, const std::string&, std::string&>;

    public:
        explicit ResizingArrayOfStringIterator(pointer p) : ptr_{p} {}

        reference operator*() const { return *ptr_; }

        auto& operator++()
        {
            ++ptr_;

            return *this;
        }

        auto operator++(int)
        {
            auto it = *this;
            ++(*this);

            return it;
        }

        template<bool R>
        bool operator==(const ResizingArrayOfStringIterator<R>& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }

        template<bool R>
        bool operator!=(const ResizingArrayOfStringIterator<R>& rhs) const
        {
            return ptr_ != rhs.ptr_;
        }

    private:
        pointer ptr_;
    };

    using const_iterator = ResizingArrayOfStringIterator<true>;
    using iterator = ResizingArrayOfStringIterator<false>;

    iterator begin()
    {
        return iterator{&array_[0]};
    }

    iterator end()
    {
        return iterator {&array_[size_]};
    }

    const_iterator begin() const
    {
        return const_iterator{&array_[0]};
    }

    const_iterator end() const
    {
        return const_iterator {&array_[size_]};
    }
private:
    void resize(int max)
    {
        auto* temp = new std::string[max];
        for (int i = 0; i < size_; ++i)
            temp[i] = array_[i];

        delete[] array_;

        array_ = temp;
        capacity_ = max;
    }

    int size_;
    int capacity_;
    std::string* array_;
};

/**
 * string for test: to be or not to - be - - that - - - is
 * result: to be not that or be (2 left on stack)
 * @return
 */
int main()
{
    ResizingArrayOfStrings q{};

    while (!StdIn::isEmpty())
    {
        std::string item = StdIn::readString();
        if (item != "-")
            q.enqueue(item);
        else if (!q.isEmpty())
            std::cout << q.dequeue() << " ";
    }
    std::cout << "(" << q.size() << " left on queue)" << std::endl;

    for (auto& item : q)
        std::cout << item << std::endl;

}
