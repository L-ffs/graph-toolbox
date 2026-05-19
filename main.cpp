#include <iostream>
#include "headders/Graph.h"


int main() {
    

    Graph graph(Representation::MATRIX, true, true);

    graph.runTests();


    // ListGraph Lgraph= ListGraph();

    // Lgraph.runIntensiveTests();

    // MatrixGraph Mgraph;
    
    // Mgraph.runIntensiveTests();

    return 0;
}