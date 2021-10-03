#include <iostream>
#include "In.h"

class UnionFind
{
public:
    UnionFind(int N) : id_{new int[N]}, count_{N}
    {
        for (int i = 0; i < N; ++i)
            id_[i] = i;
    }
    ~UnionFind() { delete[] id_; }

    int count() const { return count_; }
    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    int find(int p) { return p % 2; }
    void join(int p, int q) {}

private:
    int* id_;
    int count_;
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
