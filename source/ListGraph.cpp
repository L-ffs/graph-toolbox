#include "../headders/ListGraph.h"
#include <iostream>
#include <algorithm>

ListGraph::ListGraph() {}

ListGraph::~ListGraph() {}

void ListGraph::appendNode(int node)
{
    std::vector<ListEdge> nulledges;
    graph[node] = nulledges;
}

void ListGraph::appendEdge(int originNode, int TargetNode, size_t value, bool targeted)
{
    ListEdge edge;
    edge.trgt = TargetNode;
    edge.value = value;

    graph[originNode].push_back(edge);

    if (!targeted)
    {
        ListEdge reverse_edge;
        reverse_edge.trgt = originNode;
        reverse_edge.value = value;

        graph[TargetNode].push_back(reverse_edge);
    }
}

void ListGraph::printAdjacencyList() const
{
    for (const auto &pair : graph)
    {
        int node = pair.first;
        const std::vector<ListEdge> &edges = pair.second;

        std::cout << node << ": ";
        if (edges.empty())
        {
            std::cout << "(no edges)";
        }
        else
        {
            bool first = true;
            for (const auto &e : edges)
            {
                if (!first)
                    std::cout << ", ";
                std::cout << e.trgt << "(" << e.value << ")";
                first = false;
            }
        }
        std::cout << std::endl;
    }
}

bool ListGraph::existsEdge(int originNode, int TargetNode)
{
    for (const ListEdge &edge : graph[originNode])
    {
        if (edge.trgt == TargetNode)
            return true;
    }
    return false;
}

void ListGraph::changeEdgeValue(int originNode, int TargetNode, size_t newValue)
{
    for (ListEdge &e : graph[originNode])
    {
        if (e.trgt == TargetNode)
        {
            e.value = newValue;
            break;
        }
    }
    for (ListEdge &e : graph[TargetNode])
    {
        if (e.trgt == originNode)
        {
            e.value = newValue;
            return;
        }
    }
    std::cout << "falha ao alterar valor de aresta [" << originNode << "," << TargetNode << "]. aresta nao encontrada\n";
    exit(-1);
}

void ListGraph::deleteEdge(int originNode, int targetNode, bool targeted)
{
    for (ListEdge &edge : graph[originNode])
    {
        if (edge.trgt == targetNode)
        {
            auto it = std::find(graph[originNode].begin(), graph[originNode].end(), edge);
            if (it != graph[originNode].end())
            {
                std::move(it + 1, graph[originNode].end(), it);
                graph[originNode].pop_back();
            }
        }
    }
    if (!targeted)
    {
        for (ListEdge &edge : graph[targetNode])
        {
            if (edge.trgt == originNode)
            {
                auto it = std::find(graph[targetNode].begin(), graph[targetNode].end(), edge);
                if (it != graph[targetNode].end())
                {
                    std::move(it + 1, graph[targetNode].end(), it);
                    graph[targetNode].pop_back();
                }
            }
        }
    }
}

void ListGraph::deleteNode(int node)
{
    std::vector<int> neighbors;
    for (auto pair : graph)
    {
        if (pair.first == node)
            continue;
        for (auto edge : pair.second)
        {
            if (edge.trgt == node)
            {
                neighbors.push_back(pair.first);
                break;
            }
        }
    }
    for (auto n : neighbors)
        deleteEdge(n, node, true);
    graph.erase(node);
}

std::vector<int> ListGraph::listNeighbors(int node)
{
    std::vector<int> neighbors;
    for (auto edge : graph[node])
    {
        if (edge.trgt == node)
            continue;
        neighbors.push_back(edge.trgt);
    }
    return neighbors;
}
