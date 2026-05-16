#include "headders/ListGraph.h"
#include <iostream>
#include <algorithm>

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

    bool ListGraph::existsEdge(std::string originNode, std::string TargetNode) {

        for ( ListEdge edge : graph[originNode]) {
            if (edge.trgt_name == TargetNode) {
                return true;
            }
        }
        return false;
    }
void ListGraph::changeEdgeValue(std::string originNode, std::string TargetNode, size_t newValue) {

    for (ListEdge &e : graph[originNode]) { //graph[originNode] é um vector
        if (e.trgt_name == TargetNode) {
            e.value= newValue;
            break;
        }
    }
    for (ListEdge &e : graph[TargetNode]) { 
        if (e.trgt_name == originNode) {
            e.value= newValue;
            return;
        }
    }
    std::cout << "falha ao alterar valor de aresta [" << originNode << "," << TargetNode << "]. aresta nao encontrada\n";
    exit(-1); 
}

void ListGraph::deleteEdge(std::string originNode, std::string targetNode, bool targeted){

    for (ListEdge &edge : graph[originNode]) {
        if (edge.trgt_name == targetNode) {
            
            //trecho de codigo de IA
            auto it = std::find(graph[originNode].begin(), graph[originNode].end(), edge);

            if (it != graph[originNode].end()) {
                // 2. Move todos os elementos após o "30" uma casa para a esquerda
                // Isso joga o valor que estava no fim para a última posição de forma segura
                std::move(it + 1, graph[originNode].end(), it);

                // 3. Remove fisicamente o último elemento
                graph[originNode].pop_back(); 
            }

        }
    }
    if (!targeted) {
       
        for (ListEdge &edge : graph[targetNode]) {
        if (edge.trgt_name == originNode) {
            
            //trecho de codigo de IA
            auto it = std::find(graph[targetNode].begin(), graph[targetNode].end(), edge);

            if (it != graph[targetNode].end()) {
                // 2. Move todos os elementos após o "30" uma casa para a esquerda
                // Isso joga o valor que estava no fim para a última posição de forma segura
                std::move(it + 1, graph[targetNode].end(), it);

                // 3. Remove fisicamente o último elemento
                graph[targetNode].pop_back(); 
            }

        }
    }
    }
}