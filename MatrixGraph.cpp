#include "headders/MatrixGraph.h"
#include <iostream>

// Construtor e Destrutor
MatrixGraph::MatrixGraph() {}
MatrixGraph::~MatrixGraph() {}

// 1. Adicionar um Nó
void MatrixGraph::appendNode(std::string node) {
    // Inicializa a linha do novo nó vazia
    graph[node] = std::unordered_map<std::string, size_t>();
    
    // Para manter as propriedades de matriz quadrada, garantimos que todos os
    // nós conheçam esse novo nó com peso 0 (sem aresta), e vice-versa.
    for (auto& pair : graph) {
        std::string existingNode = pair.first;
        graph[node][existingNode] = 0;
        graph[existingNode][node] = 0;
    }
}

// 2. Adicionar uma Aresta
void MatrixGraph::appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted) {
    graph[originNode][TargetNode] = value;

    if (!targeted) {
        graph[TargetNode][originNode] = value;
    }
}

// 3. Imprimir a Matriz de Adjacência
void MatrixGraph::printAdjacencyMatrix() const {
    if (graph.empty()) {
        std::cout << "Grafo vazio." << std::endl;
        return;
    }

    // Imprime o cabeçalho com os nomes dos nós
    std::cout << "\t";
    for (const auto& pair : graph) {
        std::cout << pair.first << "\t";
    }
    std::cout << "\n";

    // Imprime as linhas da matriz
    for (const auto& rowPair : graph) {
        std::cout << rowPair.first << "\t"; // Nome do nó da linha
        for (const auto& colPair : graph) {
            // Busca o peso para a interseção da linha atual com a coluna atual
            auto it = rowPair.second.find(colPair.first);
            if (it != rowPair.second.end()) {
                std::cout << it->second << "\t";
            } else {
                std::cout << "0\t";
            }
        }
        std::cout << "\n";
    }
}

// 4. Verificar se a Aresta Existe
bool MatrixGraph::existsEdge(std::string originNode, std::string TargetNode) {
    // Se o nó de origem existe e o peso para o destino for maior que 0, a aresta existe
    if (graph.count(originNode) && graph[originNode].count(TargetNode)) {
        return graph[originNode][TargetNode] > 0;
    }
    return false;
}

// 5. Alterar o Valor (Peso) de uma Aresta
void MatrixGraph::changeEdgeValue(std::string originNode, std::string TargetNode, size_t newValue) {
    bool updated = false;

    if (existsEdge(originNode, TargetNode)) {
        graph[originNode][TargetNode] = newValue;
        updated = true;
    }

    // Se o grafo for não-direcionado, a aresta de volta também deve existir e ser atualizada
    if (existsEdge(TargetNode, originNode)) {
        graph[TargetNode][originNode] = newValue;
        updated = true;
    }

    if (!updated) {
        std::cout << "falha ao alterar valor de aresta [" << originNode << "," << TargetNode << "]. aresta nao encontrada\n";
        exit(-1);
    }
}

// 6. Deletar uma Aresta
void MatrixGraph::deleteEdge(std::string originNode, std::string targetNode, bool targeted) {
    // Na matriz, deletar significa voltar o peso para 0
    if (graph.count(originNode)) {
        graph[originNode][targetNode] = 0;
    }

    if (!targeted && graph.count(targetNode)) {
        graph[targetNode][originNode] = 0;
    }
}

// 7. Deletar um Nó por Completo
void MatrixGraph::deleteNode(std::string node) {
    // 1. Remove a linha inteira do nó
    graph.erase(node);

    // 2. Varre as linhas dos outros nós para remover a coluna referente a este nó
    for (auto& pair : graph) {
        pair.second.erase(node);
    }
}

// 8. Listar os Vizinhos de um Nó
std::vector<std::string> MatrixGraph::listNeighbors(std::string node) {
    std::vector<std::string> neighbors;

    if (graph.count(node)) {
        for (const auto& pair : graph[node]) {
            std::string targetNode = pair.first;
            size_t weight = pair.second;

            // Pula loops (nó apontando para si mesmo) se quiser o mesmo comportamento da sua lista
            if (targetNode == node) continue;

            // Se o peso for maior que 0, significa que há uma conexão (vizinho)
            if (weight > 0) {
                neighbors.push_back(targetNode);
            }
        }
    }

    return neighbors;
}



//roda testes da classe
void MatrixGraph::runIntensiveTests() {
    //metodo implementado por IA, mas revisado
    std::cout << "====================================================\n";
    std::cout << "  INICIANDO TESTES INTENSIVOS (MatrixGraph)         \n";
    std::cout << "====================================================\n\n";

    // -----------------------------------------------------
    // Teste 1: Inserção de Nós
    // -----------------------------------------------------
    std::cout << "[Teste 1] Inserindo nos (A, B, C, D)... ";
    appendNode("A");
    appendNode("B");
    appendNode("C");
    appendNode("D");
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 2: Inserção de Arestas e Direcionamento
    // -----------------------------------------------------
    std::cout << "[Teste 2] Configurando arestas (Dir. e Nao-Dir.)... ";
    // Aresta não-direcionada entre A e B (peso 10)
    appendEdge("A", "B", 10, false); 
    // Aresta direcionada de B para C (peso 20)
    appendEdge("B", "C", 20, true);  
    // Aresta não-direcionada entre C e D (peso 30)
    appendEdge("C", "D", 30, false); 

    // Validações com assert
    assert(existsEdge("A", "B") == true);
    assert(existsEdge("B", "A") == true);  // Deve ser true pois não é direcionada
    assert(existsEdge("B", "C") == true);
    assert(existsEdge("C", "B") == false); // Deve ser false pois é direcionada B -> C
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 3: Alteração de Valores (Pesos)
    // -----------------------------------------------------
    std::cout << "[Teste 3] Alterando pesos de arestas... ";
    changeEdgeValue("A", "B", 99);
    changeEdgeValue("B", "C", 50);
    
    // Garantindo que elas ainda existem após a alteração
    assert(existsEdge("A", "B") == true);
    assert(existsEdge("B", "C") == true);
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 4: Listagem de Vizinhos
    // -----------------------------------------------------
    std::cout << "[Teste 4] Verificando vizinhos dos nos... ";
    // Vizinhos de A deve ser apenas o B
    std::vector<std::string> vizinhosA = listNeighbors("A");
    assert(vizinhosA.size() == 1);
    assert(vizinhosA[0] == "B");

    // Vizinhos de B devem ser A (da aresta não-dir) e C (da aresta dir)
    std::vector<std::string> vizinhosB = listNeighbors("B");
    assert(vizinhosB.size() == 2);
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 5: Remoção de Arestas
    // -----------------------------------------------------
    std::cout << "[Teste 5] Deletando arestas específicas... ";
    // Remove a aresta não-direcionada A <-> B
    deleteEdge("A", "B", false); 
    assert(existsEdge("A", "B") == false);
    assert(existsEdge("B", "A") == false);
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 6: Remoção de Nós (O Teste mais crítico)
    // -----------------------------------------------------
    std::cout << "[Teste 6] Deletando no por completo e limpando matriz... ";
    // Antes de deletar C: B->C existe (peso 50) e D<->C existe (peso 30)
    assert(existsEdge("B", "C") == true);
    assert(existsEdge("D", "C") == true);

    // Deleta o nó C do mapa
    deleteNode("C");

    // Agora, nenhuma menção a C deve existir nas arestas dos outros nós
    assert(existsEdge("B", "C") == false);
    assert(existsEdge("D", "C") == false);
    
    // O nó D que antes tinha C como vizinho, agora deve ter 0 vizinhos
    std::vector<std::string> vizinhosD = listNeighbors("D");
    assert(vizinhosD.empty());
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    std::cout << "\n====================================================\n";
    std::cout << "  PARABENS! TODOS OS TESTES PASSARAM COM SUCESSO! 🎉 \n";
    std::cout << "====================================================\n\n";
}