#ifndef ALGORITHMS4THEDITION_BST_H
#define ALGORITHMS4THEDITION_BST_H

#include <iostream>
#include <vector>

template<class Key, class Value>
class BST
{
    class Node;
    using NodePtr = Node*;

    class Node
    {
    public:
        Key key;
        Value val;
        NodePtr left, right;
        int N;

        Node(Key key, Value val, int N)
            : key{key}, val{val}, N{N}, left{nullptr}, right{nullptr} {}
    };

public:
    BST() : root{nullptr} {}
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

    void removeMin() { root = removeMin(root); }

    void remove(Key key) { root = remove(root , key); }

    std::vector<Key> keys() { return keys(min(), max());}

    std::vector<Key> keys(Key lo, Key hi)
    {
        std::vector<Key> vector;
        keys(root, vector, lo, hi);

        return vector;
    }

private:
    Value& get(NodePtr x, Key key)
    {
        if (x == nullptr) throw std::out_of_range("key doesn't exist.");

        if      ( key < x->key) return get(x->left, key);
        else if (key > x->key) return get(x->right, key);
        else return x->val;
    }

    NodePtr put (NodePtr x, Key key, Value val)
    {
        if (x == nullptr) return new Node(key, val, 1);
        if      (key < x->key) x->left  = put(x->left, key, val);
        else if (key > x->key) x->right = put(x->right, key, val);
        else x->val = val;

        x->N = size(x->left) + size(x->right) + 1;

        return x;
    }

    NodePtr min(NodePtr x)
    {
        if (x->left == nullptr) return x;

        return min(x->left);
    }

    NodePtr max(NodePtr x)
    {
        if (x->right == nullptr) return x;

        return max(x->right);
    }

    NodePtr floor(NodePtr x, Key key)
    {
        if (x == nullptr) throw std::out_of_range("key doesn't exist.");

        if (key == x->key) return x;
        if (key < x->key) return floor(x->left, key);

        NodePtr t = floor(x->right, key);
        if (t != nullptr) return t;
        else              return x;
    }

    NodePtr select(NodePtr x, int k)
    {
        if (x == nullptr) throw std::invalid_argument("node x cannot be nullptr.");

        int t = size(x->left);
        if      (t > k) return select(x->left, k);
        else if (t < k) return select(x->right, k - t - 1);
        else            return x;
    }

    int rank(Key key, NodePtr x)
    {
        if (x == nullptr) return 0;

        if      (key < x->key)  return rank(key, x->left);
        else if (key > x->key)  return 1 + size(x->left) + rank(key, x->right);
        else return size(x->left);
    }

    NodePtr removeMin(NodePtr x)
    {
        if (x->left == nullptr)
        {
            NodePtr tmpPtr = x->right;
            delete x;

            return tmpPtr;
        }

        x->left = removeMin(x->left);
        x->N = size(x->left) + size(x->right) + 1;
        return x;
    }

    NodePtr remove(NodePtr x, Key key)
    {
        if (x == nullptr) throw std::out_of_range("key doesn't exist.");

        if      (key < x->key) x->left = remove(x->left, key);
        else if (key > x->key) x->right = remove(x->right, key);
        else
        {
            NodePtr tmpRight= x->right;
            NodePtr tmpLeft = x->left;

            delete x;
            if (tmpRight == nullptr)
            {
                return tmpLeft;
            }
            if (tmpLeft == nullptr)
            {
                return tmpRight;
            }

            x = min(tmpRight);
            x->right = removeMin(tmpRight);
            x->left = tmpLeft;
        }

        x->N = size(x->left) + size(x->right) + 1;

        return x;
    }

    void keys(NodePtr x, std::vector<Key>& vector, Key lo, Key hi)
    {
        if ( x == nullptr) return;
        if (lo < x->key) keys(x->left, vector, lo, hi);
        if ((lo == x->key || lo < x->key) && (hi == x->key || hi > x->key)) vector.push_back(x->key);
        if (hi > x->key) keys(x->right, vector, lo, hi);
    }

private:
    NodePtr root;
};


#endif //ALGORITHMS4THEDITION_BST_H
