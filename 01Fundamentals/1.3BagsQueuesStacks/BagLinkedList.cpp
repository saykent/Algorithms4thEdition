#include <iostream>
#include "StdIn.h"

template<typename T>
class Bag
{
    class Node;

public:
    Bag() : first_{nullptr} {}

    void add(T item)
    {
        Node* oldFirst = first_;
        first_ = new Node{item, nullptr};
        first_->next = oldFirst;
    }
    template<bool Const>
    class StackIterator
    {
        friend class Stack;
        friend class StackIterator<!Const>;

        using NodePtr = std::conditional_t<Const, const Node*, Node*>;
        using ItemReference = std::conditional_t<Const, const T&, T&>;
    public:
        explicit StackIterator(NodePtr p) : ptr_{p}
        {}

        ItemReference operator*() const { return ptr_->item; }

        auto& operator++()
        {
            ptr_ = ptr_->next;

            return *this;
        }

        auto operator++(int)
        {
            auto it = *this;
            ++*this;
            return it;
        }

        template<bool R>
        bool operator==(const StackIterator<R>& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }

        template<bool R>
        bool operator!=(const StackIterator<R>& rhs) const
        {
            return ptr_ != rhs.ptr_;
        }

    private:
        Node* ptr_;
    };

    using const_iterator = StackIterator<true>;
    using iterator = StackIterator<false>;

    iterator begin()
    {
        return iterator{first_};
    }

    iterator end()
    {
        return iterator{nullptr};
    }

    const_iterator begin() const
    {
        return const_iterator{first_};
    }

    const_iterator end() const
    {
        return const_iterator{nullptr};
    }
private:
    class Node
    {
    public:
        T item;
        Node* next;

        Node(T i, Node* n) : item(i), next(n) {}
    };

    Node* first_;
};

/**
 * string for test: to be or not to - be - - that - - - is
 * @return
 */
int main()
{
    Bag<std::string> b{};

    while (!StdIn::isEmpty())
    {
        std::string item = StdIn::readString();
        if (item != "-")
            b.add(item);
    }

    for (auto& item : b)
    {
        std::cout << item << std::endl;
    }
}