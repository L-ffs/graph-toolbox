#include "headders/MatrixGraph.h"
#include <iostream>
#include <queue>

// Construtor e Destrutor
MatrixGraph::MatrixGraph(bool directed) {
    isDirected = directed;
}
MatrixGraph::~MatrixGraph() {}

//Adicionar um Nó
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

//Adicionar uma Aresta
void MatrixGraph::appendEdge(std::string originNode, std::string TargetNode, size_t value, bool targeted) {
    graph[originNode][TargetNode] = value;

    if (!targeted) {
        graph[TargetNode][originNode] = value;
    }
}

//Imprimir a Matriz de Adjacência
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
        std::cout << rowPair.first << "\t"; //Nome do no da linha
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

//Verificar se a Aresta Existe
bool MatrixGraph::existsEdge(std::string originNode, std::string TargetNode) {
    if (graph.count(originNode) && graph[originNode].count(TargetNode)) {
        return graph[originNode][TargetNode] > 0;
    }
    return false;
}

//Alterar o Valor (Peso) de uma Aresta
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

//Deletar uma Aresta
void MatrixGraph::deleteEdge(std::string originNode, std::string targetNode, bool targeted) {
    // Na matriz, deletar significa voltar o peso para 0
    if (graph.count(originNode)) {
        graph[originNode][targetNode] = 0;
    }

    if (!targeted && graph.count(targetNode)) {
        graph[targetNode][originNode] = 0;
    }
}

//Deletar um Nó por Completo
void MatrixGraph::deleteNode(std::string node) {
    //Remove a linha inteira do no
    graph.erase(node);

    //Varre as linhas dos outros nós para remover a coluna referente a este no
    for (auto& pair : graph) {
        pair.second.erase(node);
    }
}

//Listar os Vizinhos de um Nó
std::vector<std::string> MatrixGraph::listNeighbors(std::string node) {
    std::vector<std::string> neighbors;

    if (graph.count(node)) {
        for (const auto& pair : graph[node]) {
            std::string targetNode = pair.first;
            size_t weight = pair.second;

            // Pula loops (nó apontando para si mesmo)
            if (targetNode == node) continue;

            // Se o peso for maior que 0, significa que há uma conexão
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
    std::cout << "[Teste 1] Inserindo nos (1, 2, 3, 4)... ";
    appendNode("1");
    appendNode("2");
    appendNode("3");
    appendNode("4");
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 2: Inserção de Arestas e Direcionamento
    // -----------------------------------------------------
    std::cout << "[Teste 2] Configurando arestas (Dir. e Nao-Dir.)... ";
    // Aresta não-direcionada entre 1 e 2 (peso 10)
    appendEdge("1", "2", 10, false); 
    // Aresta direcionada de 2 para 3 (peso 20)
    appendEdge("2", "3", 20, true);  
    // Aresta não-direcionada entre 3 e 4 (peso 30)
    appendEdge("3", "4", 30, false); 

    // Validações com assert
    assert(existsEdge("1", "2") == true);
    assert(existsEdge("2", "1") == true);  // Deve ser true pois não é direcionada
    assert(existsEdge("2", "3") == true);
    assert(existsEdge("3", "2") == false); // Deve ser false pois é direcionada 2 -> 3
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 3: Alteração de Valores (Pesos)
    // -----------------------------------------------------
    std::cout << "[Teste 3] Alterando pesos de arestas... ";
    changeEdgeValue("1", "2", 99);
    changeEdgeValue("2", "3", 50);
    
    // Garantindo que elas ainda existem após a alteração
    assert(existsEdge("1", "2") == true);
    assert(existsEdge("2", "3") == true);
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 4: Listagem de Vizinhos
    // -----------------------------------------------------
    std::cout << "[Teste 4] Verificando vizinhos dos nos... ";
    // Vizinhos de 1 deve ser apenas o 2
    std::vector<std::string> vizinhosA = listNeighbors("1");
    assert(vizinhosA.size() == 1);
    assert(vizinhosA[0] == "2");

    // Vizinhos de 2 devem ser 1 (da aresta não-dir) e 3 (da aresta dir)
    std::vector<std::string> vizinhosB = listNeighbors("2");
    assert(vizinhosB.size() == 2);
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 5: Remoção de Arestas
    // -----------------------------------------------------
    std::cout << "[Teste 5] Deletando arestas específicas... ";
    // Remove a aresta não-direcionada 1 <-> 2
    deleteEdge("1", "2", false); 
    assert(existsEdge("1", "2") == false);
    assert(existsEdge("2", "1") == false);
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    // -----------------------------------------------------
    // Teste 6: Remoção de Nós (O Teste mais crítico)
    // -----------------------------------------------------
    std::cout << "[Teste 6] Deletando no por completo e limpando matriz... ";
    // Antes de deletar 3: 2->3 existe (peso 50) e 4<->3 existe (peso 30)
    assert(existsEdge("2", "3") == true);
    assert(existsEdge("4", "3") == true);

    // Deleta o nó 3 do mapa
    deleteNode("3");

    // Agora, nenhuma menção a 3 deve existir nas arestas dos outros nós
    assert(existsEdge("2", "3") == false);
    assert(existsEdge("4", "3") == false);

    // O nó 4 que antes tinha 3 como vizinho, agora deve ter 0 vizinhos
    std::vector<std::string> vizinhosD = listNeighbors("4");
    assert(vizinhosD.empty());
    std::cout << "OK!\n";
    printAdjacencyMatrix();

    std::cout << "\n====================================================\n";
    std::cout << "  PARABENS! TODOS OS TESTES PASSARAM COM SUCESSO! 🎉 \n";
    std::cout << "====================================================\n\n";
}


//grau de Saída
size_t MatrixGraph::outDegree(std::string node) {
    // Se o nó não existir no grafo, o grau é zero
    if (graph.count(node) == 0) return 0;
    
    size_t degree = 0;
    for (const auto& edge : graph.at(node)) {
        // Na nossa matriz, peso > 0 significa que a aresta realmente existe
        if (!edge.second > 0) {
            degree++;
        }
    }   
    return degree;
}

//grau de Entrada (auxiliada por IA na logica)
size_t MatrixGraph::inDegree(std::string node) {

    if (graph.count(node) == 0) return 0;

    size_t degree = 0;

    for (const auto& rowPair : graph) {
        std::string originNode = rowPair.first;
        
        // Verificamos se esse nó de origem tem uma aresta apontando para o nosso 'node' alvo
        auto it = rowPair.second.find(node);
        if (it != rowPair.second.end() && it->second > 0) {
            degree++;
        }
    }
    return degree;
}

//adjacência
bool MatrixGraph::adjacent(std::string node1, std::string node2) {

    if (graph.count(node1) == 0 || graph.count(node2) == 0) return false;

    bool _1to2 = graph.at(node1).count(node2) && graph.at(node1).at(node2) > 0;
    bool _2to1 = graph.at(node2).count(node1) && graph.at(node2).at(node1) > 0;

    return (_1to2 || _2to1);
}

//ordenacao topológica
std::vector<std::string> MatrixGraph::topologicalSort() const{
    if (!isDirected){
        std::cout << "A Ordenação topológica só é aplicavel em grafos direcionados. Este Grafo é não Direcionado.\n";
        return {};
    }
    
    std::unordered_map<std::string, size_t> inDegree;
    
    //Este for serve para inicializar o mapa de graus de entrada, garantindo que todos os nós comecem com 0.
    for (const auto& pair : graph) {
        std::string node = pair.first;
        inDegree[node] = 0; //
    }

    for (const auto&[u, neighbours] : graph) {
        for (const auto&[v, peso]: neighbours){
            if (peso > 0 && u != v) //u!=v para evitar loops
                inDegree[v]++; // Incrementa o grau de entrada do nó v para cada aresta u->v
        }
    }

    std::queue<std::string> q;
    std::vector<std::string> topoOrder;

    for (const auto& [node, degree]: inDegree){
        if (degree == 0) {
            q.push(node); // vértices que estejam isolados ou sem dependências entram direto na fila
        }
    }

    while (!q.empty())
    {
        std::string current = q.front();
        q.pop();
        topoOrder.push_back(current);

        for(const auto&[v, peso]: graph.at(current)){
            if (peso > 0 && current != v){ //current != v para evitar loops
                inDegree[v]--; // Reduz o grau de entrada dos vizinhos

                if (inDegree[v] == 0) {
                    q.push(v); // Se um vizinho ficar sem dependências, adiciona à fila
                }
            }
        }
    }
    return (topoOrder.size() == graph.size()) ? topoOrder : std::vector<std::string>(); // Se topoOrder não incluir todos os nós, há um ciclo, e retornamos vetor vazio

}