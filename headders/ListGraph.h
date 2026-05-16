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

};


class ListGraph {
private:

    std::unordered_map<std::string, std::vector<ListEdge>> graph; //nome dos nos e sua lista de arestas

public:

    ListGraph();
    void appendNode(std::string node);
    void appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted= false);
    void printAdjacencyList() const;
    ~ListGraph();
    
};



#endif