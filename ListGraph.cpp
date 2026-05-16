#include "headders/ListGraph.h"
#include <iostream>

ListGraph::ListGraph(){
}

ListGraph::~ListGraph() {}

void ListGraph::appendNode(std::string node){
    std::vector<ListEdge> nulledges;
    graph[node]= nulledges;
}

void ListGraph::appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted){
    ListEdge edge;
    edge.trgt_name= TargetNode;
    edge.value= value;

    graph[originNode].push_back(edge);

    if(!targeted){
        ListEdge reverse_edge;
        reverse_edge.trgt_name= originNode;
        reverse_edge.value= value;

        graph[TargetNode].push_back(reverse_edge);
    }
}

void ListGraph::printAdjacencyList() const{
    for(const auto &pair : graph){
        const std::string &node = pair.first;
        const std::vector<ListEdge> &edges = pair.second;

        std::cout << node << ": ";
        if(edges.empty()){
            std::cout << "(no edges)";
        } else {
            bool first = true;
            for(const auto &e : edges){
                if(!first) std::cout << ", ";
                std::cout << e.trgt_name << "(" << e.value << ")";
                first = false;
            }
        }
        std::cout << std::endl;
    }
}
