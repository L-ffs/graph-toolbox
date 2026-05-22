#include "headders/ListGraph.h"
#include <iostream>
#include <algorithm>

ListGraph::ListGraph(){
}

ListGraph::~ListGraph() {}

void ListGraph::appendNode(int node){
    std::vector<ListEdge> nulledges;
    graph[node]= nulledges;
}

void ListGraph::appendEdge(int originNode, int TargetNode, size_t value, bool targeted){
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
        const int &node = pair.first;
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

bool ListGraph::existsEdge(int originNode, int TargetNode) {

        for ( ListEdge edge : graph[originNode]) {
            if (edge.trgt_name == TargetNode) {
                return true;
            }
        }
        return false;
}

void ListGraph::changeEdgeValue(int originNode, int TargetNode, size_t newValue) {

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

void ListGraph::deleteEdge(int originNode, int targetNode, bool targeted){

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

void ListGraph::deleteNode(int node) {
    
    
    std::vector<int> neighbors;
    for (auto pair : graph) {
        if (pair.first == node){continue;} 

        for (auto edge : pair.second) {
            
            if (edge.trgt_name == node) {

                neighbors.push_back(pair.first);
                break;
            }
        }
    }
    for (auto nodes : neighbors) {

        deleteEdge(nodes, node, true); //targeted= true pra evitar operaçoes desnecessarias
    }

    graph.erase(node);

}

std::vector<int> ListGraph::listNeighbors(int node) {

    std::vector<int> neighbors;
    
    for (auto edge : graph[node]) {
        
        if (edge.trgt_name == node) {continue;}
        
        neighbors.push_back(edge.trgt_name);
    }
    
    return neighbors;
}

