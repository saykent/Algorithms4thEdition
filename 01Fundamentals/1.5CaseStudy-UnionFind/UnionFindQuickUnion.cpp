#include <iostream>
#include "In.h"

class UnionFind
{
public:
    UnionFind(int N) : id_{new int[N]}, count_{N}, idLength_{N}
    {
        for (int i = 0; i < N; ++i)
            id_[i] = i;
        accessCount_ = 0;
    }
    ~UnionFind() { delete[] id_; }

    int count() const { return count_; }
    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    int find(int p)
    {
        //Find the root
        accessCount_++;
        while (p != id_[p])
        {
            accessCount_++;
            p = id_[p];
            accessCount_++;
        }
        return p;
    }

    void join(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) return;

        id_[pRoot] = qRoot;

        count_--;
    }

    void printContent()
    {
        std::cout << "Content: ";
        for (int i = 0; i < idLength_; ++i)
        {
            std::cout << id_[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "accessCount : " << accessCount_ << std::endl;
    }

    int maxDepth()
    {
        int max = 0;
        for (int i = 0; i < idLength_; ++i)
        {
            int depth = 1;
            int p = i;
            while (p != id_[p])
            {
                p = id_[p];
                depth++;
            }
            if (depth > max)
                max = depth;
        }

        return max;
    }

private:
    int* id_;
    int count_;
    int idLength_;
    int accessCount_;
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
    uf.printContent();
    std::cout << "Max depth : " << uf.maxDepth() << std::endl;
}
