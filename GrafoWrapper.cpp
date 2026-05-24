#include "headders/GrafoWrapper.h"

//usando matriz pq as funcoes de grau e adjacencia estao implementadas nessa representacao
GrafoWrapper::GrafoWrapper(bool orientado)
    : graph(Representation::MATRIX, orientado, true) {
}

void GrafoWrapper::inserirVertice(int vertice) {
    graph.appendNode(vertice);
}

void GrafoWrapper::inserirAresta(int origem, int destino, size_t peso) {
    //talvez tenha que ajustar tipagem se a professora pedir int para vertce e double para peso
    graph.appendEdge(origem, destino, peso);
}

bool GrafoWrapper::verificarAresta(int origem, int destino) {
    return graph.existsEdge(origem, destino);
}

void GrafoWrapper::alterarPesoAresta(int origem, int destino, size_t peso) {
    graph.changeEdgeValue(origem, destino, peso);
}

size_t GrafoWrapper::grauVertice(int vertice) {
    return graph.outDegree(vertice);
}

vector<int> GrafoWrapper::listarVizinhos(int vertice) {
    return graph.listNeighbors(vertice);
}

bool GrafoWrapper::saoAdjacentes(int origem, int destino) {
    return graph.adjacent(origem, destino);
}

void GrafoWrapper::removerAresta(int origem, int destino) {
    graph.deleteEdge(origem, destino);
}

void GrafoWrapper::removerVertice(int vertice) {
    graph.deleteNode(vertice);
}

void GrafoWrapper::exibirGrafo() const {
    graph.print();
}

vector<int> GrafoWrapper::ordemTopologica() const {
    return graph.topologicalSort();
}
