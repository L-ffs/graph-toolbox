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

    void appendNode(std::string node);
    void appendEdge(std::string originNode, std::string TargetNode, size_t value = 1);
    void print() const;
    bool existsEdge(std::string originNode, std::string TargetNode);
    void changeEdgeValue(std::string originNode, std::string TargetNode, size_t newValue);
    void deleteEdge(std::string originNode, std::string targetNode);
    void deleteNode(std::string node);
    std::vector<std::string> listNeighbors(std::string node);
    void runTests();
};



#endif