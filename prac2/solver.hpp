#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

#include "grafo/grafoMA.hpp"

using namespace std;

typedef unsigned colour;

vector<vector<colour>> C_global;

const double pps = CLOCKS_PER_SEC;
clock_t tStart;
clock_t tEnd;
bool flag_end = true;

bool no_colour_under_bound(vector<colour> Cv, colour B)
{
    for (auto c : Cv)
        if (c < B)
            return false;

    return true;
}

colour backGCP(Grafo &G, colour k, colour B, vector<vector<colour>> &C)
{
    if (((clock() - tStart) / pps) > 1200)
    {
        flag_end = false;
        return B;
    }

    // Check if there are no vertices to process
    if (!G.esConexo())
    {
        C_global = C;
        return k;
    }

    // Set of vertices that I have to process
    set<Grafo::vertice> vertices;
    for (unsigned v = 0; v < G.numVert(); v++)
        if (G.conectado(v))
            vertices.insert(v);

    // Check if there is any colour under bound
    for (auto v : vertices)
        if (no_colour_under_bound(C[v], B))
            return B;

    for (auto v : vertices)
        for (colour c : C[v])
            if (c < B)
            {
                // Modify the colour matrix
                set<unsigned> adjacents;
                for (unsigned u = 0; u < G.numVert(); u++)
                    if (u != v && G[v][u] && find(C[u].begin(), C[u].end(), c) != C[u].end())
                    {
                        adjacents.insert(u);
                        C[u][c] = C.size();
                    }

                // Modify the graph G = G - {v}
                set<unsigned> edges;
                for (unsigned i = 0; i < G.numVert(); i++)
                    if (G[v][i])
                    {
                        edges.insert(i);
                        G[v][i] = G[i][v] = false;
                    }

                // Recursive function call
                B = backGCP(G, max(k, c), B, C);

                // Restore the graph
                for (auto e : edges)
                    G[v][e] = G[e][v] = true;

                // Restore the colour matrix
                for (auto a : adjacents)
                    C[a][c] = c;
            }

    return B;
}

void solver()
{
    for (unsigned n = 5; n <= 30; n += 5)
    {
        // Get the graph from the translatorN.txt
        string t_name = "translator" + to_string(n) + ".txt";
        ifstream t(t_name);

        t.ignore(6);
        unsigned nVertices, nEdges;
        t >> nVertices >> nEdges;
        Grafo G(nVertices);

        for (unsigned i = 0; i < nVertices; i++)
            G[i][i] = true;

        string reading_line;
        while (nEdges > 0)
        {
            getline(t, reading_line);
            int v, u;
            istringstream format_line(reading_line);
            if (!format_line.eof())
            {
                t.ignore(1);
                t >> v >> u;
                G[v - 1][u - 1] = G[u - 1][v - 1] = true;
            }
            nEdges--;
        }

        t.close();

        // Aviable colour sets
        vector<vector<colour>> C(n, vector<colour>(n));
        for (unsigned i = 0; i < C.size(); i++)
            iota(C[i].begin(), C[i].end(), 0);

        C_global = C;

        // Print the solution
        cout << n << " subjects - ";

        tStart = clock();
        backGCP(G, 0, C.size(), C);
        tEnd = clock();


        if (!flag_end)
            cout << "The best solution found in 20 minutes is:" << endl;
        else 
            cout << "It has spent " << (tEnd - tStart) / pps << " seconds to find the best solution which is: " << endl;
        for (unsigned i = 0; i < C.size(); i++)
            for (unsigned j = 0; j < C.size(); j++)
                if (C_global[i][j] != C_global.size())
                {
                    cout << " - The subject with code " << i + 1 << " will have the examen the day " << C_global[i][j] + 1 << endl;
                    break;
                }

        cout << endl;
    }
}