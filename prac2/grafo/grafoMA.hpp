/*--------------------------------------------------------*/
/* grafoMA.h                                              */
/*                                                        */
/* clase Grafo: Matriz de adyacencia de un grafo.         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* �2016 José Fidel Argudo                                */
/* �2023 María Segura Bolaños (modificaciones)            */
/*--------------------------------------------------------*/

#ifndef GRAFO_MADY_H
#define GRAFO_MADY_H

#include <vector>
#include <ostream>
#include <string>

using namespace std;

template <typename tCoste>
class GrafoP;

class Grafo
{
public:
   typedef size_t vertice;

   explicit Grafo(size_t n) : ady(n, vector<bool>(n, false)) {}
   explicit Grafo(const string &nf);
   template <typename T>
   Grafo(const GrafoP<T> &G);
   size_t numVert() const { return ady.size(); }
   const vector<bool> &operator[](vertice v) const { return ady[v]; }
   vector<bool> &operator[](vertice v) { return ady[v]; }
   bool esDirigido() const;
   bool esConexo() const;
   bool conectado(vertice i) const;
private:
   vector<vector<bool>> ady;
};

template <typename T>
Grafo::Grafo(const GrafoP<T> &G) : ady(G.numVert(), vector<bool>(G.numVert()))
{
   const size_t n = G.numVert();
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         ady[i][j] = (G[i][j] != GrafoP<T>::INFINITO);
}

std::ostream &operator<<(std::ostream &os, const Grafo &G);

#endif // GRAFO_MADY_H
