#include "SequentialSearchST.h"
#include "In.h"

using ST = SequentialSearchST<std::string, int>;

void test_client()
{
    stdio::In in;
    ST st;

    for (int i = 0; !in.isEmpty(); ++i)
    {
        std::string key = in.readString();
        st.put(key, i);
    }

    for (auto& s : st.keys())
        std::cout << s << " " << st.get(s) << std::endl;


}

void frequencyCounter(int argc, char* argv[])
{
    int minLength = std::atoi(argv[1]);
    SequentialSearchST<std::string, int> st;

    stdio::In in;

    while (!in.isEmpty())
    {
        std::string word = in.readString();
        if (word.length() < minLength) continue;
        if (!st.contains(word)) st.put(word, 1);
        else                         st.put(word, st.get(word) + 1);
    }

    std::string max;
    st.put(max, 0);
    for (auto& word : st.keys())
        if (st.get(word) > st.get(max))
            max = word;

    std::cout << max << " " << st.get(max) << std::endl;
}

int main(int argc, char* argv[])
{
    //test_client();
    frequencyCounter(argc, argv);
}