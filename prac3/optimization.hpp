#include <fstream>
#include <string>
#include <sstream>
#include <set>

#include "search.hpp"

void binarySearch(const Grafo &G, int bottom, int top, int &highK)
{
    if (top >= bottom)
    {
        int k = bottom + (top - bottom) / 2;
        clique_to_sat(G, k);
        if (decision(G, k))
        {
            highK = k;
            binarySearch(G, k + 1, top, highK);
        }
        else
            binarySearch(G, bottom, k - 1, highK);
    }
}

set<unsigned> optimization(const Grafo &G, unsigned &k)
{
    // Best case: G is a clique
    k = G.numVert();
    clique_to_sat(G, k);
    if (decision(G, k))
        return search(G, k);

    // Worst case: G has no clique
    int highK = -1;
    binarySearch(G, 0, G.numVert() - 1, highK);
    if (highK == -1)
        return set<unsigned>();

    // The maximum clique of the graph is of size highK
    k = highK;
    return search(G, k);
}