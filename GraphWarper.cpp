#include "headders/GraphWrapper.h"

// usando matriz pq as funcoes de grau e adjacencia estao implementadas nessa representacao
GrafoWrapper::GrafoWrapper(bool orientado)
    : graph(Representation::MATRIX, orientado, true)
{
}

void GrafoWrapper::inserirVertice(string vertice)
{
    if (nameToId.find(vertice) == nameToId.end())
    {
        int id = nextId++;
        nameToId[vertice] = id;
        idToName.push_back(vertice);
        graph.appendNode(id);
    }
}

void GrafoWrapper::inserirAresta(string origem, string destino, size_t peso)
{
    // talvez tenha que ajustar tipagem se a professora pedir int para vertce e double para peso
    if (nameToId.find(origem) == nameToId.end())
        inserirVertice(origem);
    if (nameToId.find(destino) == nameToId.end())
        inserirVertice(destino);
    int idO = nameToId[origem];
    int idD = nameToId[destino];
    graph.appendEdge(idO, idD, peso);
}

bool GrafoWrapper::verificarAresta(string origem, string destino)
{
    if (nameToId.find(origem) == nameToId.end() || nameToId.find(destino) == nameToId.end())
        return false;
    return graph.existsEdge(nameToId[origem], nameToId[destino]);
}

void GrafoWrapper::alterarPesoAresta(string origem, string destino, size_t peso)
{
    if (nameToId.find(origem) == nameToId.end() || nameToId.find(destino) == nameToId.end())
        return;
    graph.changeEdgeValue(nameToId[origem], nameToId[destino], peso);
}

size_t GrafoWrapper::grauVertice(string vertice)
{
    if (nameToId.find(vertice) == nameToId.end())
        return 0;
    return graph.outDegree(nameToId[vertice]);
}

vector<string> GrafoWrapper::listarVizinhos(string vertice)
{
    std::vector<string> result;
    if (nameToId.find(vertice) == nameToId.end())
        return result;
    std::vector<int> neighbors = graph.listNeighbors(nameToId[vertice]);
    for (int id : neighbors)
    {
        if (id >= 0 && id < (int)idToName.size())
            result.push_back(idToName[id]);
        else
            result.push_back(std::to_string(id));
    }
    return result;
}

bool GrafoWrapper::saoAdjacentes(string origem, string destino)
{
    if (nameToId.find(origem) == nameToId.end() || nameToId.find(destino) == nameToId.end())
        return false;
    return graph.adjacent(nameToId[origem], nameToId[destino]);
}

void GrafoWrapper::removerAresta(string origem, string destino)
{
    if (nameToId.find(origem) == nameToId.end() || nameToId.find(destino) == nameToId.end())
        return;
    graph.deleteEdge(nameToId[origem], nameToId[destino]);
}

void GrafoWrapper::removerVertice(string vertice)
{
    if (nameToId.find(vertice) == nameToId.end())
        return;
    int id = nameToId[vertice];
    graph.deleteNode(id);
    // remover do mapeamento (simplesmente marca vazio no idToName)
    if (id >= 0 && id < (int)idToName.size())
        idToName[id] = "";
    nameToId.erase(vertice);
}

void GrafoWrapper::exibirGrafo() const
{
    graph.print();
}

std::vector<std::string> GrafoWrapper::ordenacaoTopologica() const
{
    std::vector<std::string> result;
    std::vector<int> ids = graph.topologicalSort();
    if (ids.empty()) return result;
    for (int id : ids) {
        if (id >= 0 && id < (int)idToName.size() && !idToName[id].empty())
            result.push_back(idToName[id]);
        else
            result.push_back(std::to_string(id));
    }
    return result;
}
