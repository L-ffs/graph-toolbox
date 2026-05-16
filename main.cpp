#include <iostream>
#include "headders/ListGraph.h"

int main() {
    std::cout << "hrllo world\n";
    
    ListGraph graph= ListGraph();

    graph.appendNode("node1");
    graph.appendNode("node@");
    graph.appendEdge("node1", "node@", 10, false);

    std::cout <<"\n\n";
    graph.printAdjacencyList();
    std::cout <<"\n\n";

    std::cout << "a aresta [node1, node@] existe? " << (graph.existsEdge("node1", "node@") ? "sim" : "nao") << "\n\n";

    graph.changeEdgeValue("node1", "node@", 3);

    std::cout <<"\n\n";
    graph.printAdjacencyList();
    std::cout <<"\n\n";

    graph.deleteEdge("node1", "node@", true);

    std::cout <<"\n\n";
    graph.printAdjacencyList();
    std::cout <<"\n\n";

    return 0;
}