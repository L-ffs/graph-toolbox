#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>

class MatrixGraph
{

private:
    std::unordered_map<int, std::unordered_map<int, size_t>> graph;

    /*        [no1]  [no2]
        [no1] peso   peso

        [no2] peso   peso
    */
    bool isDirected = true;

public:
    MatrixGraph(bool directed = false);
    ~MatrixGraph();

    // Manipulação Básica de Grafos
    void appendNode(int node);

    void appendEdge(int originNode, int TargetNode, size_t value, bool targeted = false);

    void printAdjacencyMatrix() const;

    // Consultas e Modificações de Grafos

    bool existsEdge(int originNode, int TargetNode);

    void changeEdgeValue(int originNode, int TargetNode, size_t newValue);

    void deleteEdge(int originNode, int targetNode, bool targeted = false);

    void deleteNode(int node);

    // Informações para Vértices

    std::vector<int> listNeighbors(int node);

    size_t outDegree(int node); // a implementar
    size_t inDegree(int node);
    bool adjacent(int node1, int node2);

    // Utilitários de Testes, feito por IA, mas revisado
    void runIntensiveTests();

    // Ordenação topológica (Utilizando ALgoritmo de Kahn, pois já identifica ciclos)
    std::vector<int> topologicalSort() const;
    bool isDAG() const { return !topologicalSort().empty(); } // Retorna true se o grafo for um Grafo direcionado acíclico, ou seja, se a ordenação topológica é possível
};

#endif