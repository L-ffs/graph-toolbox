#include <iostream>
#include "headders/ListGraph.h"

int main() {
    std::cout << "hrllo world\n";
    
    ListGraph graph= ListGraph();

    graph.appendNode("node1");
    graph.appendNode("node@");
    graph.appendEdge("node1", "node@", 10, true);

    std::cout <<"\n\n";
    graph.printAdjacencyList();
    std::cout <<"\n\n";


    return 0;
}