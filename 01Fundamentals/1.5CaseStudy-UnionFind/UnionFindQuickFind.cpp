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
        accessCount_++;
        return id_[p];
    }
    void join(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);

        if (pId == qId) return;

        for (int i = 0; i < idLength_; ++i)
        {
            accessCount_++;
            if (id_[i] == pId)
            {
                accessCount_++;
                id_[i] = qId;
            }
        }

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
}
