#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>



class ListEdge {
public:

    //escolhida representaçoes menos eficientes em memoria visando a didatica da representaçao
    std::string trgt_name;
    size_t value;
    bool operator==(const ListEdge &other) { //operador usado pelo trecho de IA
        return (trgt_name == other.trgt_name && value == other.value);
    }

};


class ListGraph {
private:

    std::unordered_map<std::string, std::vector<ListEdge>> graph; //map [chave]= valor de nós e sua lista de arestas

public:

    ListGraph();

    ~ListGraph();
    
    void appendNode(std::string node);

    void appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted= false);

    void printAdjacencyList() const;

    bool existsEdge(std::string originNode, std::string TargetNode);

    void changeEdgeValue(std::string originNode, std::string TargetNode, size_t newValue);

    void deleteEdge(std::string originNode, std::string targetNode, bool targeted= false);

    void deleteNode(std::string node);
    
    std::vector<std::string> listNeighbors(std::string node);
};



#endif