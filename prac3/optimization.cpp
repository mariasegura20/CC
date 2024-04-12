#include <iostream>

#include "data.hpp"
#include "optimization.hpp"

using namespace std;

int main()
{
    // Get the data
    Grafo G = get_the_graph("grafo.txt");

    // Solve the optimization problem
    unsigned k;
    set<unsigned> clique = optimization(G, k);
    if (!clique.empty())
    {
        cout << "The maximum clique is a " << k << "-clique with the vertex: ";
        for (auto v : clique)
            cout << v << " ";
        cout << endl;
    }
    else
        cout << "There is no clique in the graph." << endl;
}