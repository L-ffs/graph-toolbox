#include "headders/Graph.h"

/*arguments
Representation::<type>
bool <directed?>
bool <weighted?>*/
Graph::Graph(Representation rep, bool directed, bool weighted)
    : repType(rep), isDirected(directed), isWeighted(weighted)
{

    if (repType == Representation::LIST)
    {
        listGraph = new ListGraph();
    }
    else
    {
        matrixGraph = new MatrixGraph(directed);
    }
}

// Destrutor (evita vazamento de memória deletando a instância criada)
Graph::~Graph()
{
    delete listGraph;
    delete matrixGraph;
}

void Graph::appendNode(int node)
{
    if (repType == Representation::LIST)
    {
        listGraph->appendNode(node);
    }
    else
    {
        matrixGraph->appendNode(node);
    }
}

void Graph::appendEdge(int originNode, int TargetNode, size_t value)
{
    size_t actualValue = isWeighted ? value : 1;

    if (repType == Representation::LIST)
    {
        listGraph->appendEdge(originNode, TargetNode, actualValue, isDirected);
    }
    else
    {
        matrixGraph->appendEdge(originNode, TargetNode, actualValue, isDirected);
    }
}

void Graph::print() const
{
    if (repType == Representation::LIST)
    {
        std::cout << "--- Representacao por Lista de Adj. ---\n";
        listGraph->printAdjacencyList();
    }
    else
    {
        std::cout << "--- Representacao por Matriz de Adj. ---\n";
        matrixGraph->printAdjacencyMatrix();
    }
}

bool Graph::existsEdge(int originNode, int TargetNode)
{
    if (repType == Representation::LIST)
    {
        return listGraph->existsEdge(originNode, TargetNode);
    }
    else
    {
        return matrixGraph->existsEdge(originNode, TargetNode);
    }
}

void Graph::changeEdgeValue(int originNode, int TargetNode, size_t newValue)
{
    if (!isWeighted)
    {
        std::cout << "Aviso: Tentando alterar peso em um grafo nao-ponderado. Operacao ignorada.\n";
        return;
    }

    if (repType == Representation::LIST)
    {
        listGraph->changeEdgeValue(originNode, TargetNode, newValue);
    }
    else
    {
        matrixGraph->changeEdgeValue(originNode, TargetNode, newValue);
    }
}

void Graph::deleteEdge(int originNode, int targetNode)
{
    if (repType == Representation::LIST)
    {
        listGraph->deleteEdge(originNode, targetNode, isDirected);
    }
    else
    {
        matrixGraph->deleteEdge(originNode, targetNode, isDirected);
    }
}

void Graph::deleteNode(int node)
{
    if (repType == Representation::LIST)
    {
        listGraph->deleteNode(node);
    }
    else
    {
        matrixGraph->deleteNode(node);
    }
}

std::vector<int> Graph::listNeighbors(int node)
{
    if (repType == Representation::LIST)
    {
        return listGraph->listNeighbors(node);
    }
    else
    {
        return matrixGraph->listNeighbors(node);
    }
}

void Graph::runTests()
{
    if (repType == Representation::LIST)
    {
        std::cout << "====================================================\n";
        std::cout << "ERRO: Ainda nao existem testes para a representacao em lista.\n";
        std::cout << "====================================================\n\n";
    }
    else
    {
        // Como o método roda direto na instância da matriz, acionamos ele por aqui
        matrixGraph->runIntensiveTests();
    }
}

size_t Graph::outDegree(int node)
{
    if (repType == Representation::LIST)
    {

        std::cout << "funçao nao implementada para esse tipo de estrutura";
        exit(-1);
    }
    else
    {
        return matrixGraph->outDegree(node);
    }
}
size_t Graph::inDegree(int node)
{

    if (repType == Representation::LIST)
    {
        std::cout << "funçao nao implementada para esse tipo de estrutura";
        exit(-1);
    }
    else
    {
        return matrixGraph->inDegree(node);
    }
}
bool Graph::adjacent(int node1, int node2)
{

    if (repType == Representation::LIST)
    {

        std::cout << "funçao nao implementada para esse tipo de estrutura";
        exit(-1);
    }
    else
    {
        return matrixGraph->adjacent(node1, node2);
    }
}

size_t Graph::degree(int node)
{
    if (!isDirected)
    {
        return static_cast<size_t>(this->outDegree(node));
    }
    else
    {
        return static_cast<size_t>(this->outDegree(node) + this->inDegree(node));
    }
}

std::vector<int> Graph::topologicalSort() const {
    if (repType == Representation::LIST) {
        return {};
    } else {
        return matrixGraph->topologicalSort();
    }
}
