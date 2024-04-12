#include <iostream>

#include "data.hpp"
#include "decision.hpp"

using namespace std;

int main()
{
    // Get the data
    Grafo G = get_the_graph("grafo.txt");
    cout << "Size of the clique: ";
    unsigned k;
    cin >> k;

    // Solve the decision problem
    if (decision(G, k))
        cout << "There is at least one " << k << "-clique in the graph." << endl;
    else
        cout << "There isn't any " << k << "-clique in the graph." << endl;
}