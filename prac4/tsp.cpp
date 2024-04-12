#include <ctime>
#include <iostream>

#include "tsp.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: ./tsp.exe <string>" << endl;
        return 1;
    }

    string filename = argv[1];

    // Get the graph of the cities
    string filenameMap = "TSPLIB/" + filename + ".tsp";
    GrafoP G = tsp_to_graph(filenameMap);

    // Initial clock
    double t0 = clock();

    // Initial solution
    // pair<vector<unsigned>, double> actualSolution = greedy(G);

    // Initial solution
    pair<vector<unsigned>, double> actualSolution = randomSolution(G);

    // Initial temperature
    double T = 50 * G.numVert();

    // Simulated Annealing
    uniform_real_distribution<> dis(0.0, 1.0);
    while (T > 0.1)
    {
        // Generate the neighbor solution
        pair<vector<unsigned>, double> newSolution = swapPath(actualSolution, G);

        if (newSolution.second < actualSolution.second)
            actualSolution = newSolution;
        else
        {
            double P = exp((actualSolution.second - newSolution.second) / T);
            random_device rd;
            mt19937 g(rd());
            if (dis(g) < P)
                actualSolution = newSolution;
        }
        T = T * 0.99999;
    }

    // Final clock
    double t1 = clock();

    // Best solution found
    string filenameSolution = filename + ".best.tour";
    solution_to_tsp(filenameSolution, actualSolution);
    cout << "Solution: " << actualSolution.second << endl;

    // Optimal solution
    string filenameTour = "TSPLIB/" + filename + ".opt.tour";
    double optFitness = optimalFitness(filenameTour, G);
    cout << "Optimal fitness: " << optFitness << endl << endl;

    // Interesting data
    cout << "Running time: " << (t1 - t0) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Absolute error: " << actualSolution.second - optFitness << endl;
    cout << "Relative error: " << (actualSolution.second - optFitness) / optFitness << endl;
}