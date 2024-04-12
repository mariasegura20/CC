#include <fstream>
#include <string>
#include <sstream>
#include <set>

#include "decision.hpp"

set<unsigned> search(Grafo G, unsigned k)
{
    clique_to_sat(G, k);
    if (!decision(G, k))
        return set<unsigned>();

    set<unsigned> clique;
    for (unsigned v = 0; v < G.numVert() && clique.size() < k; v++)
    {
        // Remove the processed vertex
        set<unsigned> adjacents = G.adyacentes(v);
        G.putZeros(v);

        clique_to_sat(G, k);
        if (!decision(G, k))
        {
            // Restore the processed vertex if it belong to the clique
            clique.insert(v + 1);
            for (auto a : adjacents)
                G[v][a] = G[a][v] = true;
        }
    }

    return clique;
}