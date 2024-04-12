#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>

#include "grafoP.hpp"

using namespace std;

struct Coordinates
{
    double x, y;
    Coordinates(int x = 0, int y = 0) : x(x), y(y) {}
};

double euclideanDistance(const Coordinates &c1, const Coordinates &c2)
{
    return sqrt(pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2));
}

GrafoP tsp_to_graph(string filenameMap)
{
    // Get the number of cities
    ifstream f(filenameMap);
    string reading_line;
    for (unsigned i = 0; i < 3; i++)
        getline(f, reading_line);
    f.ignore(11);

    unsigned nCities;
    f >> nCities;

    for (unsigned i = 0; i < 2; i++)
        getline(f, reading_line);

    // Get the coordinates
    vector<Coordinates> cities(nCities);
    for (unsigned i = 0; i < nCities; i++)
    {
        getline(f, reading_line);
        double v, x, y;
        f >> v >> x >> y;
        cities[v - 1] = Coordinates(x, y);
    }
    f.close();

    // Get the graph
    GrafoP G(nCities);
    for (unsigned i = 0; i < nCities - 1; i++)
        for (unsigned j = i + 1; j < nCities; j++)
            G[i][j] = G[j][i] = euclideanDistance(cities[i], cities[j]);

    return G;
}

// First version of the initial solution (finally not used)
pair<vector<unsigned>, double> greedy(const GrafoP &G)
{
    GrafoP cities(G);
    const unsigned nCities = cities.numVert();

    double fitness = 0;
    vector<unsigned> path;
    unsigned nCitiesVisited = 0;

    // Origin
    unsigned origin = 1;
    unsigned actualCity = origin;
    path.push_back(origin);
    for (unsigned i = 0; i < nCities; i++)
        cities[i][origin] = GrafoP::INFINITO;
    nCitiesVisited++;

    // Path
    while (nCitiesVisited < nCities)
    {
        auto actualDist = min_element(cities[actualCity].begin(), cities[actualCity].end());
        fitness += *actualDist;
        actualCity = distance(cities[actualCity].begin(), actualDist);
        path.push_back(actualCity);
        for (unsigned i = 0; i < nCities; i++)
            cities[i][actualCity] = GrafoP::INFINITO;
        nCitiesVisited++;
    }

    fitness += G[origin][actualCity];

    return make_pair(path, fitness);
}

pair<vector<unsigned>, double> randomSolution(const GrafoP &G)
{
    const unsigned nCities = G.numVert();

    vector<unsigned> path(nCities);
    iota(path.begin(), path.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(path.begin() + 1, path.end(), g);

    double fitness = 0;
    for (unsigned i = 0; i < nCities - 1; i++)
        fitness += G[path[i]][path[i + 1]];
    fitness += G[path[nCities - 1]][path[0]];
    
    return make_pair(path, fitness);
}

pair<vector<unsigned>, double> swapPath(const pair<vector<unsigned>, double> &actualSolution, const GrafoP &G)
{
    vector<unsigned> path = actualSolution.first;
    double fitness = actualSolution.second;
    const unsigned nCities = path.size();

    // Generate the indices of the vector path that are going to be changed
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> dis(1, nCities - 1);
    int index1 = dis(g);
    int index2 = dis(g);

    fitness -= G[path[index1 - 1]][path[index1]];
    fitness -= G[path[index1]][path[(index1 + 1) % nCities]];
    fitness -= G[path[index2 - 1]][path[index2]];
    fitness -= G[path[index2]][path[(index2 + 1) % nCities]];

    // Change the path
    uniform_real_distribution<> dis2(0.0, 1.0);
    if (dis2(g) > 0.5)
        swap(path[index1], path[index2]);
    else
        for (unsigned i = 0 ; (index1 + i) < (index2 - i) ; i++)
            swap(path[index1 + i], path[index2 - i]);

    fitness += G[path[index1 - 1]][path[index1]];
    fitness += G[path[index1]][path[(index1 + 1) % nCities]];
    fitness += G[path[index2 - 1]][path[index2]];
    fitness += G[path[index2]][path[(index2 + 1) % nCities]];
    
    return make_pair(path, fitness);
}

void solution_to_tsp(string filenameSolution, const pair<vector<unsigned>, double> &solution)
{
    string filename = "BestSolutionsTSP/" + filenameSolution;
    ofstream f(filename);

    f << "NAME : " << filenameSolution << endl;
    f << "TYPE : TOUR" << endl;
    f << "DIMENSION : " << solution.first.size() << endl;
    f << "TOUR_SECTION" << endl;
    for (auto c : solution.first)
        f << c + 1 << endl;
    f << "EOF";

    f.close();
}

double optimalFitness(string filenameTour, const GrafoP &G)
{
    // Get the tour
    ifstream f(filenameTour);
    string reading_line;
    for (unsigned i = 0; i < 3; i++)
        getline(f, reading_line);

    const unsigned nCities = G.numVert();
    vector<unsigned> tour;
    for (unsigned i = 0; i < nCities; i++)
    {
        getline(f, reading_line);
        unsigned c;
        f >> c;
        tour.push_back(c - 1);
    }

    double fitness = 0;

    for (unsigned i = 0; i < nCities - 1; i++)
        fitness += G[tour[i]][tour[i + 1]];
    fitness += G[tour[nCities - 1]][tour[0]];

    return fitness;
}