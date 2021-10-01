#include <iostream>
#include "StdIn.h"

template<typename T>
class Queue
{
    class Node;

public:
    bool isEmpty() { return first_ == nullptr; }
    int size() { return N_; }

    void enqueue(T item)
    {
        Node* oldLast = last_;
        last_ = new Node{item, nullptr};
        if (isEmpty())  first_ = last_;
        else            oldLast->next = last_;
        N_++;
    }

    T dequeue()
    {
        T item = first_->item;
        first_ = first_->next;
        if (isEmpty()) last_ = nullptr;
        N_--;

        return item;
    }

    template<bool Const>
    class QueueIterator
    {
        friend class Queue;
        friend class QueueIterator<!Const>;

        using NodePtr = std::conditional_t<Const, const Node*, Node*>;
        using ItemReference = std::conditional_t<Const, const T&, T&>;

    public:
        explicit QueueIterator(NodePtr p) : ptr_{p} {}

        ItemReference operator*() const { return ptr_->item; }

        auto& operator++()
        {
            ptr_ = ptr_->next;

            return *this;
        }

        auto operator++(int)
        {
            auto it = *this;
            ++(*this);

            return it;
        }

        template<bool R>
        bool operator++(const QueueIterator<R>& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }

        template<bool R>
        bool operator!=(const QueueIterator<R>& rhs) const
        {
            return ptr_ != rhs.ptr_;
        }

    private:
        Node* ptr_;
    };

    using const_iterator = QueueIterator<true>;
    using iterator = QueueIterator<false>;

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
    Node* last_;
    int N_;
};

/**
 * string for test: to be or not to - be - - that - - - is
 * result: to be not that or be (2 left on stack)
 * @return
 */
int main()
{
    Queue<std::string> q{};

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