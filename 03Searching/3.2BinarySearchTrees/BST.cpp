#include "BST.h"
#include "In.h"


int main(int argc, char* argv[])
{
    int minLength = std::atoi(argv[1]);
    BST<std::string, int> bst;

    stdio::In in;

    while (!in.isEmpty())
    {
        std::string word = in.readString();
        if (word.length() < minLength) continue;
        if (!bst.contains(word)) bst.put(word, 1);
        else                         bst.put(word, bst.get(word) + 1);
    }

    std::string max;
    bst.put(max, 0);
    for (auto& word : bst.keys())
        if (bst.get(word) > bst.get(max))
            max = word;

    std::cout << max << " " << bst.get(max) << std::endl;
}
