#ifndef ALGORITHMS4THEDITION_BAG_H
#define ALGORITHMS4THEDITION_BAG_H

#include <vector>

template<class DataIterator, bool Const>
class BagIterator
{
    using IteratorPointer = std::conditional_t<Const, const DataIterator*, DataIterator*>;
    using reference = std::conditional_t<Const, const typename DataIterator::value_type&, typename DataIterator::value_type&>;

public:
    explicit BagIterator(DataIterator iterator) : iterator_{iterator}
    {
    }

    reference operator*() const { return *iterator_; }
    auto& operator++()
    {
        ++iterator_;
        return *this;
    }
    auto operator++(int)
    {
        auto it = *this;
        ++*this;
        return it;
    }

    template<bool R>
    bool operator==(const BagIterator<DataIterator, R>& rhs) const
    {
        return iterator_ == rhs.iterator_;
    }

    template<bool R>
    bool operator!=(const BagIterator<DataIterator, R>& rhs) const
    {
        return iterator_ != rhs.iterator_;
    }

    //support explicit conversion of iterator to const_iterator (but not vice versa)
    explicit operator BagIterator<DataIterator, true>() const
    {
        return BagIterator<DataIterator, true>{iterator_};
    }

private:
    DataIterator iterator_;
};

template<typename T>
class Bag
{
public:
    using const_iterator = BagIterator<typename std::vector<T>::iterator, true>;
    using iterator = BagIterator<typename std::vector<T>::iterator, false>;

    Bag() = default;
    void add(T item);
    bool isEmpty();
    int size();

    iterator begin() { return iterator{data_.begin()}; }
    iterator end() { return iterator{data_.end()}; }
    const_iterator begin() const { return const_iterator{data_.begin()}; }
    const_iterator end() const { return const_iterator{data_.end()}; }

private:
    std::vector<T> data_;
};

#endif //ALGORITHMS4THEDITION_BAG_H
