#include <iostream>

#include "data.hpp"
#include "search.hpp"

using namespace std;

int main()
{
    // Get the data
    Grafo G = get_the_graph("grafo.txt");
    cout << "Size of the clique: ";
    unsigned k;
    cin >> k;

    // Solve the search problem
    set<unsigned> clique = search(G, k);
    if (!clique.empty())
    {
        cout << "There is a " << k << "-clique in the graph with the vertex: ";
        for (auto v : clique)
            cout << v << " ";
        cout << endl;
    }
    else
        cout << "There isn't any " << k << "-clique in the graph." << endl;
}