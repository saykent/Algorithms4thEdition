#include <iostream>
#include "In.h"

class UnionFind
{
public:
    UnionFind(int N) : id_{new int[N]}, size_{new int[N]}, count_{N}, idLength_{N}
    {
        for (int i = 0; i < N; ++i)
            id_[i] = i;
        for (int i = 0; i < N; ++i)
            size_[i] = 1;
    }
    ~UnionFind()
    {
        delete[] id_;
        delete[] size_;
    }

    int count() const { return count_; }
    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    int find(int p)
    {
        //Find the root
        while (p != id_[p]) p = id_[p];
        return p;
    }

    void join(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) return;

        if (size_[pRoot] < size_[qRoot])
        {
            id_[pRoot] = qRoot;
            size_[qRoot] += size_[pRoot];
        }
        else
        {
            id_[qRoot] = pRoot;
            size_[pRoot] += size_[qRoot];
        }

        count_--;
    }

private:
    int* id_;
    int* size_;
    int count_;
    int idLength_;
};

int main()
{
    stdio::In in;
    int N = in.readInt();
    UnionFind uf{N};

    while (!in.isEmpty())
    {
        int p = in.readInt();
        int q = in.readInt();

        if (uf.connected(p, q)) continue;
        uf.join(p, q);
        std::cout << p << " " << q << std::endl;
    }

    std::cout << uf.count() << " components" << std::endl;
}
