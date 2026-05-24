#include <iostream>
#include "headders/Graph.h"
#include "headders/GraphReader.h"


int main() {
    

    Graph graph(Representation::MATRIX, true, true);

    graph.runTests();


    std::string caminhoDoArquivo = "GraphFile_Model.graph"; 
    
    Graph* meuGrafoCarregado = GraphReader::readGraphFile(caminhoDoArquivo);

    
    meuGrafoCarregado->print();

    delete meuGrafoCarregado; // verificar a possibilidade de passar o grafo por valor para evirar memoryleak


    // ListGraph Lgraph= ListGraph();

    // Lgraph.runIntensiveTests();

    // MatrixGraph Mgraph;
    
    // Mgraph.runIntensiveTests();

    return 0;
}