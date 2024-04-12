#ifndef _GRAFO_PONDERADO_HPP_
#define _GRAFO_PONDERADO_HPP_

#include <vector>
#include <limits>

using namespace std;

class GrafoP
{
public:
   static const double INFINITO;

   explicit GrafoP(unsigned n) : costes(n, vector<double>(n, INFINITO)) {}
   GrafoP(const GrafoP &G);
   unsigned numVert() const { return costes.size(); }
   const vector<double> &operator[](unsigned v) const { return costes[v]; }
   vector<double> &operator[](unsigned v) { return costes[v]; }

private:
   vector<vector<double>> costes;
};

// Definición de INFINITO
const double GrafoP::INFINITO = numeric_limits<double>::max();

// Construye un GrafoP<T> a partir de uno no ponderado representado
// mediante matriz de adyacencia, es decir, cambiando la representaci�n
// a matriz de costes con aristas de coste 1.
GrafoP::GrafoP(const GrafoP &G) : costes(G.numVert(), vector<double>(G.numVert()))
{
   const unsigned n = G.numVert();
   for (unsigned i = 0; i < n; i++)
      for (unsigned j = 0; j < n; j++)
         costes[i][j] = G[i][j];
}

ostream& operator << (ostream& os, const GrafoP& G)
{
   const unsigned n = G.numVert();
   for (unsigned i = 0 ; i < n ; i++)
   {
      for (unsigned j = 0 ; j < n ; j++)
         os << G[i][j] << " ";

      os << endl;
   }
   return os;
}

#endif // _GRAFO_PONDERADO_HPP_
