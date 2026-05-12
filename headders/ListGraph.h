#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

class ListGraph
{
private:
    std::unordered_map<std::string, ListEdge> graph;
public:
    ListGraph(std::string node, std::vector<ListEdge> Edges);
    void appendNode(std::string node);
    void appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted= false);
    ~ListGraph();
};

ListGraph::ListGraph(/* args */)
{
}

ListGraph::~ListGraph()
{
}

class ListEdge
{
private:

    //escolhida representaçoes menos eficientes em memoria visando a didatica da representaçao
    std::string trgt_name;
    size_t value;


public:
    ListEdge(std::string trgt_name, size_t value);
    ~ListEdge();
    std::string getName();
    size_t getValue();
};

ListEdge::ListEdge(std::string trgt_name, size_t value){}

ListEdge::~ListEdge(){}

std::string ListEdge::getName(){}

size_t ListEdge::getValue(){}



#endif