#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <vector>
#include <unordered_map>

// Nós são representados por inteiros internamente




class ListEdge {
public:
    int trgt; // id do nó alvo
    size_t value;
    bool operator==(const ListEdge &other) const {
        return (trgt == other.trgt && value == other.value);
    }
};

class ListGraph {
private:

    std::unordered_map<int, std::vector<ListEdge>> graph; // map [node id] -> lista de arestas

public:

    ListGraph();

    ~ListGraph();

    void appendNode(int node);

    void appendEdge(int originNode, int TargetNode, size_t value, bool targeted = false);

    void printAdjacencyList() const;

    bool existsEdge(int originNode, int TargetNode);

    void changeEdgeValue(int originNode, int TargetNode, size_t newValue);

    void deleteEdge(int originNode, int targetNode, bool targeted = false);

    void deleteNode(int node);

    std::vector<int> listNeighbors(int node);
};



#endif