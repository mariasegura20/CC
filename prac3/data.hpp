#include <fstream>
#include <sstream>

#include "grafo.hpp"

Grafo get_the_graph(string file)
{
    ifstream g(file);

    g.ignore(6);
    unsigned nVertices, nEdges;
    g >> nVertices >> nEdges;
    Grafo G(nVertices);

    string reading_line;
    while (nEdges > 0)
    {
        getline(g, reading_line);
        int v, u;
        istringstream format_line(reading_line);
        if (!format_line.eof())
        {
            g.ignore(1);
            g >> v >> u;
            G[v - 1][u - 1] = G[u - 1][v - 1] = true;
        }
        nEdges--;
    }

    g.close();

    return G;
}

unsigned vertex_to_sat(unsigned vGraph, unsigned vClique, unsigned k)
{
    return k * (vGraph - 1) + vClique;
}

void clique_to_sat(const Grafo &G, unsigned k)
{
    unsigned nVertices = G.numVert();
    unsigned nEdges = G.numEdges();

    // Count the number of variables
    int nVar = nVertices * k;

    // Count the number of clauses
    int nClauses = k; // P1
    nClauses += (nVertices * ((k - 1) * k) / 2); // P2
    unsigned noEdges = (nVertices * (nVertices - 1) / 2) - nEdges;
    nClauses += (noEdges * k * (k - 1)); // P3

    // Create the txt
    ofstream sat("sat.txt");
    sat << "p cnf " << nVar << " " << nClauses;

    // P1
    for (int r = 1; r <= k; r++)
    {
        sat << endl;
        for (int i = 1; i <= nVertices; i++)
            sat << vertex_to_sat(i, r, k) << " ";
        sat << 0;
    }

    // P2
    for (int i = 1; i <= nVertices; i++)
        for (int r = 1; r < k; r++)
            for (int s = r + 1; s <= k; s++)
                sat << endl
                    << "-" << vertex_to_sat(i, r, k) << " -" << vertex_to_sat(i, s, k) << " " << 0;

    // P3
    int cont = 0;
    for (int v = 0; v < nVertices - 1 && cont < noEdges; v++)
        for (int w = v + 1; w < nVertices && cont < noEdges; w++)
            if (!G[v][w])
            {
                for (int r = 1; r <= k; r++)
                    for (int s = 1; s <= k; s++)
                        if (r != s)
                            sat << endl
                                << "-" << vertex_to_sat(v + 1, r, k) << " -" << vertex_to_sat(w + 1, s, k) << " " << 0;

                cont++;
            }
}
