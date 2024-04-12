#include <fstream>
#include <string>
#include <sstream>

bool decision(const Grafo &G, unsigned k)
{
    clique_to_sat(G, k);
    system("./picosat-965/picosat sat.txt > picosat.txt");
    ifstream p("picosat.txt");
    p.ignore(2);
    string sol;
    getline(p, sol);
    if (sol == "SATISFIABLE")
        return true;
    else
        return false;
}