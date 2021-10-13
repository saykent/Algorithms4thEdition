#include <iostream>
#include <vector>
#include <random>

#include "2.1ElementarySorts/Stopwatch.h"
#include "2.1ElementarySorts/Insertion.h"
#include "2.1ElementarySorts/Selection.h"
#include "2.1ElementarySorts/Shell.h"
#include "2.2Mergesort/Merge.h"
#include "2.2Mergesort/MergeBU.h"
#include "2.3QuickSort/Quick.h"

class SortCompare
{
public:
    static double time(const std::string& alg, std::vector<double> a)
    {
        Insertion<double> insertion;
        Selection<double> selection;
        Shell<double> shell;
        Merge<double> merge;
        MergeBU<double> mergeBU;
        Quick<double> quick;

        Stopwatch timer;
        if      (alg == "Selection")    selection.sort(a);
        else if (alg == "Insertion")    insertion.sort(a);
        else if (alg == "Shell")        shell.sort(a);
        else if (alg == "Merge")        merge.sort(a);
        else if (alg == "MergeBU")      mergeBU.sort(a);
        else if (alg == "Quick")        quick.sort(a);

        return timer.elapsedTime();
    }

    static double timeRandomInput(const std::string& alg, int N, int T)
    {
        double total = 0.0;
        std::vector<double> a(N);

        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        for (int t = 0; t < T; ++t)
        {
            for (int i = 0; i < N; ++i)
                a[i] = distribution(generator);
            total += time(alg, a);
        }

        return total;
    }
};


int main(int argc, char* argv[])
{
    std::string alg1 = argv[1];
    std::string alg2 = argv[2];

    int N = std::atoi(argv[3]);
    int T = std::atoi(argv[4]);

    double t1 = SortCompare::timeRandomInput(alg1, N, T);
    double t2 = SortCompare::timeRandomInput(alg2, N, T);

    std::cout << "For " << N << " random doubles" << std::endl;
    std::cout << "Elapsed time " << alg1 << ": " << t1 << ", " << alg2 << ": " << t2 << std::endl;
    std::cout << "    " << alg1 << " is" << std::endl;
    std::cout << " " << t2/t1 << " times faster than " << alg2 << std::endl;
}