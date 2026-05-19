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
    

public:
    MatrixGraph(/* args */);
    ~MatrixGraph();


    void appendNode(std::string node);

    void appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted = false);

    void printAdjacencyMatrix() const; 

    bool existsEdge(std::string originNode, std::string TargetNode);

    void changeEdgeValue(std::string originNode, std::string TargetNode, size_t newValue);

    void deleteEdge(std::string originNode, std::string targetNode, bool targeted = false);

    void deleteNode(std::string node);

    std::vector<std::string> listNeighbors(std::string node);

    //metodo implementado por IA, mas revisado
    void runIntensiveTests();
};








#endif