#ifndef GRAPH_H
#define GRAPH_H


#include "ListGraph.h"
#include "MatrixGraph.h"
#include <iostream>

enum class Representation { LIST, MATRIX };

class Graph {
private:
    Representation repType; 
    bool isDirected;       
    bool isWeighted;       

    ListGraph* listGraph = nullptr;
    MatrixGraph* matrixGraph = nullptr;

public:
    Graph(Representation rep, bool directed, bool weighted);
    ~Graph();

    void appendNode(int node);
    void appendEdge(int originNode, int TargetNode, size_t value = 1);
    void print() const;
    bool existsEdge(int originNode, int TargetNode);
    void changeEdgeValue(int originNode, int TargetNode, size_t newValue);
    void deleteEdge(int originNode, int targetNode);
    void deleteNode(int node);
    std::vector<int> listNeighbors(int node);
    void runTests();
    size_t outDegree(int node);
    size_t inDegree(int node);
    size_t degree(int node);
    bool adjacent(int node1, int node2);
    std::vector<int> topologicalSort() const;

};



#endif