#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>



class ListEdge {
public:

    //escolhida representaçoes menos eficientes em memoria visando a didatica da representaçao
    int trgt_name;
    size_t value;
    bool operator==(const ListEdge &other) { //operador usado pelo trecho de IA
        return (trgt_name == other.trgt_name && value == other.value);
    }

};


class ListGraph {
private:

    std::unordered_map<int, std::vector<ListEdge>> graph; //map [chave]= valor de nós e sua lista de arestas

public:

    ListGraph();

    ~ListGraph();
    
    void appendNode(int node);

    void appendEdge(int originNode, int TargetNode, size_t value, bool targeted= false);

    void printAdjacencyList() const;

    bool existsEdge(int originNode, int TargetNode);

    void changeEdgeValue(int originNode, int TargetNode, size_t newValue);

    void deleteEdge(int originNode, int targetNode, bool targeted= false);

    void deleteNode(int node);
    
    std::vector<int> listNeighbors(int node);
};



#endif