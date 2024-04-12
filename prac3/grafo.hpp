#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <vector>
#include <set>

using namespace std;

class Grafo
{
public:
	explicit Grafo(size_t n);
	Grafo(const Grafo &G);
	const vector<bool> &operator[](unsigned v) const { return adyacencia[v]; }
	vector<bool> &operator[](unsigned v) { return adyacencia[v]; }
	size_t numVert() const { return adyacencia.size(); }
	size_t numEdges() const;
	bool esConexoG() const;
	bool esConexoV(unsigned v) const;
	set<unsigned> adyacentes(unsigned v) const;
	void putZeros(unsigned v);

private:
	vector<vector<bool>> adyacencia;
};

Grafo::Grafo(size_t n) : adyacencia(n, vector<bool>(n, false))
{
	for (unsigned i = 0; i < n; i++)
		adyacencia[i][i] = true;
}

Grafo::Grafo(const Grafo &G) : adyacencia(G.numVert(), vector<bool>(G.numVert(), false))
{
	size_t n = G.numVert();
	for (unsigned u = 0; u <= n - 1; u++)
		for (unsigned v = 0; v <= n - 1; v++)
			adyacencia[u][v] = G[u][v];
}

size_t Grafo::numEdges() const
{
	size_t n = 0;
	for (unsigned i = 0; i < adyacencia.size(); i++)
		for (unsigned j = i + 1; j < adyacencia.size(); j++)
			if (adyacencia[i][j] && i != j)
				n++;
	return n;
}

bool Grafo::esConexoG() const
{
	for (unsigned i = 0; i < adyacencia.size(); i++)
		for (unsigned j = 0; j < adyacencia.size(); j++)
			if (adyacencia[i][j] && i != j)
				return true;
	return false;
}

bool Grafo::esConexoV(unsigned v) const
{
	for (unsigned i = 0; i < adyacencia.size(); i++)
		if (adyacencia[v][i] && v != i)
			return true;
	return false;
}

set<unsigned> Grafo::adyacentes(unsigned v) const
{
	set<unsigned> adj;
	for (unsigned i = 0; i < adyacencia.size(); i++)
	{
		if (adyacencia[v][i])
			adj.insert(i);
	}
	return adj;
}

void Grafo::putZeros(unsigned v)
{
	for (unsigned u = 0; u < adyacencia.size(); u++)
		adyacencia[u][v] = adyacencia[v][u] = false;
}

#endif