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

    void inserirVertice(string vertice);
    void inserirAresta(string origem, string destino, size_t peso = 1);
    bool verificarAresta(string origem, string destino);
    void alterarPesoAresta(string origem, string destino, size_t peso);
    size_t grauVertice(string vertice);
    vector<string> listarVizinhos(string vertice);
    bool saoAdjacentes(string origem, string destino);
    void removerAresta(string origem, string destino);
    void removerVertice(string vertice);
    void exibirGrafo() const;
};

#endif
