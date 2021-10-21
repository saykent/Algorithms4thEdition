#ifndef ALGORITHMS4THEDITION_SEQUENTIALSEARCHST_H
#define ALGORITHMS4THEDITION_SEQUENTIALSEARCHST_H
#include <iostream>

template<class Key, class Value>
class SequentialSearchST
{
    class Node;
    using NodePtr = Node*;

    class Node
    {
    public:
        Node(Key key, Value value, NodePtr next)
            : key_{key}, value_{value}, next_{next}
        {
        }

        Key key_;
        Value value_;
        NodePtr next_;
    private:
    };

    template<bool Const>
    class Iterator
    {
        friend class SequentialSearchST;
        friend class Iterator<!Const>;

        using KeyReference = std::conditional_t<Const, const Key&, Key&>;
    public:
        explicit Iterator(NodePtr p) : ptr_{p} {}

        KeyReference operator*() const { return ptr_->key_; }

        auto& operator++()
        {
            ptr_ = ptr_->next_;

            return *this;
        }

        auto operator++(int)
        {
            auto it = *this;
            ++*this;
            return it;
        }

        template<bool R>
        bool operator==(const Iterator<R>& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }

        template<bool R>
        bool operator!=(const Iterator<R>& rhs) const
        {
            return ptr_ != rhs.ptr_;
        }

    private:
        NodePtr ptr_;
    };

    class NodeKeyIterator
    {
        friend class SequentialSearchST;
    public:
        explicit NodeKeyIterator(NodePtr nodePtr) : first_{nodePtr} {}

        using const_iterator = Iterator<true>;
        using iterator = Iterator<false>;

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
        NodePtr first_;
    };

public:
    SequentialSearchST() : first_{nullptr}, size_{0} {}

    Value get(const Key& key)
    {
        for (NodePtr x = first_; x != nullptr; x = x->next_)
        {
            if (key == x->key_)
                return x->value_;
        }

        throw std::out_of_range("key doesn't exist.");
    }

    void put(Key key, Value value)
    {
        for (NodePtr x = first_; x != nullptr; x = x->next_)
        {
            if (key == x->key_)
            {
                x->value_ = value;
                return;
            }
        }

        first_ = new Node(key, value, first_);
        ++size_;
    }

    void remove(Key key)
    {
        NodePtr previous = nullptr;

        for (NodePtr x = first_; x != nullptr; x = x->next_)
        {
            if (key == x->key_)
            {
                if (x == first_)
                    first_ = x->next_;
                else
                    previous->next_ = x->next_;
                --size_;

                delete x;

                break;
            }
            else
                previous = x;
        }
    }

    bool contains(Key key)
    {
        for (NodePtr x = first_; x != nullptr; x = x->next_)
        {
            if (key == x->key_)
                return true;
        }

        return false;
    }

    int size() { return size_; }
    bool isEmpty() { return size_ == 0;}

    NodeKeyIterator keys()
    {
        NodeKeyIterator keyIterator{first_};

        return keyIterator;
    }


private:
    NodePtr first_;
    int size_;
};


#endif //ALGORITHMS4THEDITION_SEQUENTIALSEARCHST_H
