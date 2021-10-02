#include <iostream>

template<typename T>
class Stack
{
    class Node;

public:
    Stack() : N_(0), first_(nullptr) {}

    bool isEmpty() { return first_ == nullptr; }
    int size()      { return N_; }
    void push(T item)
    {
        Node* oldFirst = first_;
        first_ = new Node{item, oldFirst};
        N_++;
    }

    T pop()
    {
        Node* oldFirst = first_;
        T item = first_->item;
        first_ = first_->next;
        N_--;

        delete oldFirst;

        return item;
    }

    T peek()
    {
        return first_->item;
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
        Node(T& i, Node* n) : item(i), next(n) {}
    };

    Node* first_;
    int N_;
};
