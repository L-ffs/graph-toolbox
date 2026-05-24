#ifndef GRAFOWRAPPER_H
#define GRAFOWRAPPER_H

#include "Graph.h"

// Inclui size_t usado nas assinaturas do wrapper
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

class GrafoWrapper {
private:
    Graph graph;

public:
    GrafoWrapper(bool orientado);

    void inserirVertice(int vertice);
    void inserirAresta(int origem, int destino, size_t peso = 1);
    bool verificarAresta(int origem, int destino);
    void alterarPesoAresta(int origem, int destino, size_t peso);
    size_t grauVertice(int vertice);
    vector<int> listarVizinhos(int vertice);
    bool saoAdjacentes(int origem, int destino);
    void removerAresta(int origem, int destino);
    void removerVertice(int vertice);
    void exibirGrafo() const;
    vector<int> ordemTopologica() const;
};

#endif
