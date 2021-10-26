#ifndef ALGORITHMS4THEDITION_REDBLACKBST_H
#define ALGORITHMS4THEDITION_REDBLACKBST_H

#include <iostream>
#include <vector>

template<class Key, class Value>
class RedBlackBST
{
    class Node;
    using NodePtr = Node*;

    static const bool RED = true;
    static const bool BLACK = false;

    class Node
    {
    public:
        Key key;
        Value val;
        NodePtr left, right;
        int N;
        bool color;

        Node(Key key, Value val, int N, bool color)
                : key{key}, val{val}, N{N}, left{nullptr}, right{nullptr}, color{color} {}
    };

public:
    RedBlackBST() : root{nullptr} {}
    int size() { return size(root); }
    bool isEmpty() { return root == nullptr; }

    bool contains(Key key)
    {
        if (!isEmpty())
        {
            try
            {
                get(root, key);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        return false;
    }

    int size(NodePtr x)
    {
        if (x == nullptr) return 0;
        else              return x->N;
    }

    Value& get(Key key) { return get(root, key); }

    void put(Key key, Value val)
    {
        root = put(root, key, val);
        root->color = BLACK;
    }

    Key min() { return min(root)->key; }
    Key max() { return max(root)->key; }

    Key floor(Key key)
    {
        NodePtr x = floor(root, x);

        return x->key;
    }

    Key select(int k)
    {
        return select(root, k)->key;
    }

    int rank(Key key) { return rank(key, root); }

    std::vector<Key> keys() { return keys(min(), max());}

    std::vector<Key> keys(Key lo, Key hi)
    {
        std::vector<Key> vector;
        keys(root, vector, lo, hi);

        return vector;
    }
private:
    bool isRed(NodePtr x)
    {
        if (x == nullptr) return false;
        return x->color == RED;
    }

    NodePtr rotateLeft(NodePtr h)
    {
        NodePtr x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = 1 + size(h->left) + size(h->right);

        return x;
    }

    NodePtr rotateRight(NodePtr h)
    {
        NodePtr x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = 1 + size(h->left) + size(h->right);

        return x;
    }

    void flipColors(NodePtr h)
    {
        h->color = RED;
        h->left->color = BLACK;
        h->right->color = BLACK;
    }

    Value& get(NodePtr x, Key key)
    {
        if (x == nullptr) throw std::out_of_range("key doesn't exist.");

        if      ( key < x->key) return get(x->left, key);
        else if (key > x->key) return get(x->right, key);
        else return x->val;
    }

    NodePtr put (NodePtr h, Key key, Value val)
    {
        if (h == nullptr) return new Node(key, val, 1, RED);

        if      (key < h->key) h->left  = put(h->left, key, val);
        else if (key > h->key) h->right = put(h->right, key, val);
        else h->val = val;

        if (isRed(h->right) && !isRed(h->left))     h = rotateLeft(h);
        if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
        if (isRed(h->left) && isRed(h->right))      flipColors(h);

        h->N = size(h->left) + size(h->right) + 1;

        return h;
    }
private:
    NodePtr root;
};


#endif //ALGORITHMS4THEDITION_REDBLACKBST_H
