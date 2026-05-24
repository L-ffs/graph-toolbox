#include "headders/Graph.h"

/*arguments
Representation::<type>
bool <directed?>
bool <weighted?>*/
Graph::Graph(Representation rep, bool directed, bool weighted) 
    : repType(rep), isDirected(directed), isWeighted(weighted) {
    
    if (repType == Representation::LIST) {
        listGraph = new ListGraph();
    } else {
        matrixGraph = new MatrixGraph();
    }
}

// Destrutor (evita vazamento de memória deletando a instância criada)
Graph::~Graph() {
    delete listGraph;
    delete matrixGraph;
}

void Graph::appendNode(std::string node) {
    if (repType == Representation::LIST) {
        listGraph->appendNode(node);
    } else {
        matrixGraph->appendNode(node);
    }
}

void Graph::appendEdge(std::string originNode, std::string TargetNode, size_t value) {
    size_t actualValue = isWeighted ? value : 1;

    if (repType == Representation::LIST) {
        listGraph->appendEdge(originNode, TargetNode, actualValue, isDirected);
    } else {
        matrixGraph->appendEdge(originNode, TargetNode, actualValue, isDirected);
    }
}

void Graph::print() const {
    if (repType == Representation::LIST) {
        std::cout << "--- Representacao por Lista de Adj. ---\n";
        listGraph->printAdjacencyList();
    } else {
        std::cout << "--- Representacao por Matriz de Adj. ---\n";
        matrixGraph->printAdjacencyMatrix();
    }
}

bool Graph::existsEdge(std::string originNode, std::string TargetNode) {
    if (repType == Representation::LIST) {
        return listGraph->existsEdge(originNode, TargetNode);
    } else {
        return matrixGraph->existsEdge(originNode, TargetNode);
    }
}

void Graph::changeEdgeValue(std::string originNode, std::string TargetNode, size_t newValue) {
    if (!isWeighted) {
        std::cout << "Aviso: Tentando alterar peso em um grafo nao-ponderado. Operacao ignorada.\n";
        return;
    }

    if (repType == Representation::LIST) {
        listGraph->changeEdgeValue(originNode, TargetNode, newValue);
    } else {
        matrixGraph->changeEdgeValue(originNode, TargetNode, newValue);
    }
}

void Graph::deleteEdge(std::string originNode, std::string targetNode) {
    if (repType == Representation::LIST) {
        listGraph->deleteEdge(originNode, targetNode, isDirected);
    } else {
        matrixGraph->deleteEdge(originNode, targetNode, isDirected);
    }
}

void Graph::deleteNode(std::string node) {
    if (repType == Representation::LIST) {
        listGraph->deleteNode(node);
    } else {
        matrixGraph->deleteNode(node);
    }
}

std::vector<std::string> Graph::listNeighbors(std::string node) {
    if (repType == Representation::LIST) {
        return listGraph->listNeighbors(node);
    } else {
        return matrixGraph->listNeighbors(node);
    }
}

void Graph::runTests() {
    if (repType == Representation::LIST) {
        std::cout << "====================================================\n";
        std::cout << "ERRO: Ainda nao existem testes para a representacao em lista.\n";
        std::cout << "====================================================\n\n";
    } else {
        // Como o método roda direto na instância da matriz, acionamos ele por aqui
        matrixGraph->runIntensiveTests();
    }
}


size_t Graph::outDegree(std::string node) {
    if (repType == Representation::LIST) {

        std::cout << "funçao nao implementada para esse tipo de estrutura";
        exit(-1);
        
    } else {
        return matrixGraph->outDegree(node);
    }
}
size_t Graph::inDegree(std::string node) {

    if (repType == Representation::LIST) {
        std::cout << "funçao nao implementada para esse tipo de estrutura";
        exit(-1);
    } else {
        return matrixGraph->inDegree(node);
    }
}
bool Graph::adjacent(std::string node1, std::string node2) {

    if (repType == Representation::LIST) {
        
        std::cout << "funçao nao implementada para esse tipo de estrutura";
        exit(-1);
    } else {
        return matrixGraph->adjacent(node1, node2);
    }
}

size_t Graph::degree(std::string node) {
    if(!isDirected){
        return static_cast<size_t>(this->outDegree(node));
    }
    else{
        return static_cast<size_t>(this->outDegree(node) + this->inDegree(node));
    }
}

std::vector<std::string> Graph::topologicalSort() const {
    if (repType == Representation::LIST) {
        std::cout << "funçao nao implementada para esse tipo de estrutura";
        exit(-1);
    } else {
        return matrixGraph->topologicalSort();
    }
}


