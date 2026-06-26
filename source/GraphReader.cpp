#include "../headders/GraphReader.h"
#include "../headders/Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

std::vector<std::string> GraphReader::parseGraphLine(const std::string &line)
{

    std::vector<std::string> tokens;
    std::string currentToken = "";
    bool insideParam = false;
    int openParentheses = 0;

    for (char c : line)
    {
        if (c == '(')
        {
            openParentheses++;
            if (openParentheses > 1 && !insideParam)
            {
                insideParam = true;
                currentToken = "";
            }
        }
        else if (c == ')')
        {
            openParentheses--;
            if (insideParam && openParentheses == 1)
            {
                insideParam = false;
                tokens.push_back(currentToken);
            }
        }
        else
        {
            if (insideParam)
            {
                currentToken += c;
            }
        }
    }
    return tokens;
}

Graph *GraphReader::readGraphFile(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cout << "Erro: Nao foi possivel abrir o arquivo no caminho: " << filePath << "\n";
        return nullptr;
    }

    Representation rep = Representation::MATRIX;
    bool directed = false;
    bool weighted = false;

    std::string line;
    std::vector<EdgeData> temporaryEdges;
    std::unordered_set<std::string> uniqueNodes;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        // 1. Processamento do Cabeçalho (Tags)
        if (line.find("tipo:") != std::string::npos)
        {
            if (line.find("lista") != std::string::npos)
                rep = Representation::LIST;
            if (line.find("matriz") != std::string::npos)
                rep = Representation::MATRIX;
        }
        else if (line.find("direcionado:") != std::string::npos)
        {
            if (line.find("sim") != std::string::npos || line.find("true") != std::string::npos)
            {
                directed = true;
            }
        }
        else if (line.find("ponderado:") != std::string::npos)
        {
            if (line.find("sim") != std::string::npos || line.find("true") != std::string::npos)
            {
                weighted = true;
            }
        }
        else if (line.find("((") != std::string::npos)
        {
            std::vector<std::string> tokens = parseGraphLine(line);

            if (tokens.size() >= 3)
            {
                std::string origin = tokens[0];
                std::string target = tokens[2];
                size_t weight = 1;

                if (tokens.size() >= 4)
                {
                    std::stringstream ss(tokens[3]);
                    ss >> weight;
                }

                temporaryEdges.push_back({origin, target, weight});
                uniqueNodes.insert(origin);
                uniqueNodes.insert(target);
            }
        }
    }

    file.close();

    Graph *dynamicGraph = new Graph(rep, directed, weighted);

    // Mapear nomes de nós (strings) para IDs inteiros usados internamente pela implementação de Graph
    std::unordered_map<std::string, int> nameToId;
    int nextId = 0;
    for (const std::string &nodeName : uniqueNodes)
    {
        int id = nextId++;
        nameToId[nodeName] = id;
        dynamicGraph->appendNode(id);
    }

    for (const auto &edge : temporaryEdges)
    {
        int idO = nameToId[edge.origin];
        int idT = nameToId[edge.target];
        dynamicGraph->appendEdge(idO, idT, edge.weight);
    }

    if (dynamicGraph == nullptr)
    {
        std::cout << "erro carregar grafo.";
        exit(-1);
    }
    return dynamicGraph;
}