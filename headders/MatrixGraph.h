#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>

class MatrixGraph {

private:

    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> graph;

    /*        [no1]  [no2]
        [no1] peso   peso

        [no2] peso   peso
    */
   bool isDirected = true;
    

public:
    MatrixGraph(bool directed = false);
    ~MatrixGraph();

    //Manipulação Básica de Grafos
    void appendNode(std::string node);

    void appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted = false);

    void printAdjacencyMatrix() const; 

    //Consultas e Modificações de Grafos

    bool existsEdge(std::string originNode, std::string TargetNode);

    void changeEdgeValue(std::string originNode, std::string TargetNode, size_t newValue);

    void deleteEdge(std::string originNode, std::string targetNode, bool targeted = false);

    void deleteNode(std::string node);

    //Informações para Vértices

    std::vector<std::string> listNeighbors(std::string node);

    size_t outDegree(std::string node); //a implementar
    size_t inDegree(std::string node);
    bool adjacent(std::string node1, std::string node2);

    //Utilitários de Testes, feito por IA, mas revisado
    void runIntensiveTests();

    //Ordenação topológica (Utilizando ALgoritmo de Kahn, pois já identifica ciclos)
    std::vector<std::string> topologicalSort() const;
    bool isDAG() const {return !topologicalSort().empty();}// Retorna true se o grafo for um Grafo direcionado acíclico, ou seja, se a ordenação topológica é possível 
};








#endif