#ifndef ALGORITHMS4THEDITION_BINARYSEARCHST_H
#define ALGORITHMS4THEDITION_BINARYSEARCHST_H

#include <iostream>
#include <vector>

template<class Key, class Value>
class BinarySearchST
{
    template<bool Const>
    class Iterator
    {
        friend class SequentialSearchST;
        friend class Iterator<!Const>;

        using KeyReference = std::conditional_t<Const, const Key&, Key&>;
        using IteratorType = typename std::vector<Key>::iterator;
    public:
        explicit Iterator(IteratorType it) : it_{it} {}

        KeyReference operator*() const { return *it_; }

        auto& operator++()
        {
            ++it_;

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
            return it_ == rhs.it_;
        }

        template<bool R>
        bool operator!=(const Iterator<R>& rhs) const
        {
            return it_ != rhs.it_;
        }

    private:
        typename std::vector<Key>::iterator it_;
    };

public:
    BinarySearchST() : N_{0} {}
    int size() { return N_; }
    bool isEmpty() { return N_ == 0; }

    Value& get(Key key)
    {
        if (!isEmpty())
        {
            int i = rank(key);
            if (i < N_ && keys_[i] == key)
                return values_[i];
        }

        throw std::out_of_range("key does not exist.");
    }

    int rank(Key key)
    {
        int lo = 0, hi = N_ - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (key < keys_[mid])       hi = mid - 1;
            else if (key > keys_[mid])  lo = mid + 1;
            else return mid;
        }

        return lo;
    }

    void put(Key key, Value value)
    {
        int i = rank(key);
        if (i < N_ && keys_[i] == key)
        {
            values_[i] = value;
            return;
        }

        keys_.insert(keys_.begin() + i, key);
        values_.insert(values_.begin() + i, value);
        ++N_;
    }

    void remove(Key key)
    {
        if (!isEmpty())
        {
            int i = rank(key);
            if (i < N_ && keys_[i] == key)
            {
                keys_.erase(keys_.begin() + i);
                values_.erase(values_.begin() + i);
                --N_;
            }
        }
    }

    bool contains(Key key)
    {
        if (!isEmpty())
        {
            int i = rank(key);
            if (i < N_ && keys_[i] == key)
                return true;
        }

        return false;
    }

    std::vector<Key> keys()
    {

        return keys_;
    }

    std::vector<Key> keys(Key lo, Key hi)
    {
        std::vector<Key> partialKeys;
        for (int i = rank(lo); i < rank(hi); ++i)
            partialKeys.push_back(keys_[i]);

        if (contains(hi))
            partialKeys.push_back(keys_[rank(hi)]);

        return partialKeys;
    }

private:
    std::vector<Key> keys_;
    std::vector<Value> values_;
    int N_;
};


#endif //ALGORITHMS4THEDITION_BINARYSEARCHST_H
