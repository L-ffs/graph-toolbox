#include "GraphWrapper.h"

//usando matriz pq as funcoes de grau e adjacencia estao implementadas nessa representacao
GrafoWrapper::GrafoWrapper(bool orientado)
    : graph(Representation::MATRIX, orientado, true) {
}

void GrafoWrapper::inserirVertice(string vertice) {
    graph.appendNode(vertice);
}

void GrafoWrapper::inserirAresta(string origem, string destino, size_t peso) {
    //talvez tenha que ajustar tipagem se a professora pedir int para vertce e double para peso
    graph.appendEdge(origem, destino, peso);
}

bool GrafoWrapper::verificarAresta(string origem, string destino) {
    return graph.existsEdge(origem, destino);
}

void GrafoWrapper::alterarPesoAresta(string origem, string destino, size_t peso) {
    graph.changeEdgeValue(origem, destino, peso);
}

size_t GrafoWrapper::grauVertice(string vertice) {
    return graph.outDegree(vertice);
}

vector<string> GrafoWrapper::listarVizinhos(string vertice) {
    return graph.listNeighbors(vertice);
}

bool GrafoWrapper::saoAdjacentes(string origem, string destino) {
    return graph.adjacent(origem, destino);
}

void GrafoWrapper::removerAresta(string origem, string destino) {
    graph.deleteEdge(origem, destino);
}

void GrafoWrapper::removerVertice(string vertice) {
    graph.deleteNode(vertice);
}

void GrafoWrapper::exibirGrafo() const {
    graph.print();
}

vector<string> GrafoWrapper::ordenacaoTopologica() const {
    return graph.topologicalSort();
}
