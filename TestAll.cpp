#include "TestAll.h"
#include "headders/GraphWrapper.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestAll::testAll() {
    GrafoWrapper gNaoOrientado(false);
    GrafoWrapper gOrientado(true);

    int passou = 0;
    int falhou = 0;
    int excecoes = 0;

    cout << "==================================================\n";
    cout << "              BATERIA DE TESTES \n";
    cout << "==================================================\n\n";

    cout << "--------------------------------------------------\n";
    cout << "      Fase 1: Testando Grafo Nao Orientado        \n";
    cout << "--------------------------------------------------\n\n";

    cout << "[TESTE] Inserindo vertices iniciais (0 a 5)...\n";
    try {
        vector<string> vertices = {"0", "1", "2", "3", "4", "5"};
        for (string vertice : vertices) {
            gNaoOrientado.inserirVertice(vertice);
        }
        cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        cout << "  STATUS: FALHOU (Lancou excecao ao inserir vertices)\n\n";
        excecoes++;
    }

    cout << "[TESTE] Inserindo malha de arestas...\n";
    try {
        gNaoOrientado.inserirAresta("0", "1", 1);
        gNaoOrientado.inserirAresta("0", "2", 2);
        gNaoOrientado.inserirAresta("1", "2", 1);
        gNaoOrientado.inserirAresta("2", "3", 3);
        gNaoOrientado.inserirAresta("3", "4", 4);
        gNaoOrientado.inserirAresta("4", "5", 2);
        gNaoOrientado.inserirAresta("3", "5", 5);
        cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        cout << "  STATUS: FALHOU (Lancou excecao ao inserir arestas)\n\n";
        excecoes++;
    }

    cout << "[TESTE] Verificar existencia da aresta existente (0, 1):\n";
    cout << "  Saida Esperada: VERDADEIRO\n";
    try {
        bool obtido = gNaoOrientado.verificarAresta("0", "1");
        cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (obtido) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Verificar existencia na direcao inversa (1, 0):\n";
    cout << "  Saida Esperada: VERDADEIRO\n";
    try {
        bool obtido = gNaoOrientado.verificarAresta("1", "0");
        cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (obtido) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Verificar aresta inexistente entre vertices existentes (0, 5):\n";
    cout << "  Saida Esperada: FALSO\n";
    try {
        bool obtido = gNaoOrientado.verificarAresta("0", "5");
        cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (!obtido) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Alterar peso da aresta (2, 3) para 9:\n";
    cout << "  Saida Esperada: Modificacao executada com sucesso\n";
    try {
        gNaoOrientado.alterarPesoAresta("2", "3", 9);
        cout << "  Saida Obtida:   Modificacao executada com sucesso\n  STATUS:         PASSOU\n\n";
        passou++;
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Calcular grau do vertice 2:\n";
    cout << "  Saida Esperada: 3\n";
    try {
        size_t obtido = gNaoOrientado.grauVertice("2");
        cout << "  Saida Obtida:   " << obtido << "\n";
        if (obtido == 3) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Listar vizinhos do vertice 3:\n";
    cout << "  Saida Esperada: [2, 4, 5]\n";
    try {
        vector<string> obtido = gNaoOrientado.listarVizinhos("3");
        sort(obtido.begin(), obtido.end());
        cout << "  Saida Obtida:   [";
        for (size_t i = 0; i < obtido.size(); ++i) {
            cout << obtido[i] << (i == obtido.size() - 1 ? "" : ", ");
        }
        cout << "]\n";
        bool correto = (obtido.size() == 3 && obtido[0] == "2" && obtido[1] == "4" && obtido[2] == "5");
        if (correto) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Verificar se 4 e 5 sao adjacentes em ambas as direcoes:\n";
    cout << "  Saida Esperada: (4,5)=VERDADEIRO e (5,4)=VERDADEIRO\n";
    try {
        bool dir1 = gNaoOrientado.saoAdjacentes("4", "5");
        bool dir2 = gNaoOrientado.saoAdjacentes("5", "4");
        cout << "  Saida Obtida:   (4,5): " << (dir1 ? "VERDADEIRO" : "FALSO")
             << " | (5,4): " << (dir2 ? "VERDADEIRO" : "FALSO") << "\n";
        if (dir1 && dir2) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Remover aresta (3, 4):\n";
    cout << "  Saida Esperada: FALSO para ambas as direcoes\n";
    try {
        gNaoOrientado.removerAresta("3", "4");
        bool aindaExisteDireto = gNaoOrientado.verificarAresta("3", "4");
        bool aindaExisteInverso = gNaoOrientado.verificarAresta("4", "3");
        cout << "  Saida Obtida:   Aresta (3,4) existe? " << (aindaExisteDireto ? "VERDADEIRO" : "FALSO") << "\n";
        cout << "                  Aresta (4,3) existe? " << (aindaExisteInverso ? "VERDADEIRO" : "FALSO") << "\n";
        if (!aindaExisteDireto && !aindaExisteInverso) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Remover vertice 2:\n";
    cout << "  Saida Esperada: FALSO para adjacencias antigas e grau 1 para o vertice 0\n";
    try {
        gNaoOrientado.removerVertice("2");
        bool adj02 = gNaoOrientado.saoAdjacentes("0", "2");
        bool adj12 = gNaoOrientado.saoAdjacentes("1", "2");
        size_t grauRestante0 = gNaoOrientado.grauVertice("0");
        cout << "  Saida Obtida:   Adjacente (0,2)? " << (adj02 ? "VERDADEIRO" : "FALSO")
             << " | Adjacente (1,2)? " << (adj12 ? "VERDADEIRO" : "FALSO") << "\n";
        cout << "                  Grau restante do vertice 0: " << grauRestante0 << "\n";
        if (!adj02 && !adj12 && grauRestante0 == 1) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "--------------------------------------------------\n";
    cout << "        Fase 2: Testando Grafo Orientado          \n";
    cout << "--------------------------------------------------\n\n";

    cout << "[TESTE] Inserindo vertices iniciais (0 a 5)...\n";
    try {
        vector<string> vertices = {"0", "1", "2", "3", "4", "5"};
        for (string vertice : vertices) {
            gOrientado.inserirVertice(vertice);
        }
        cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        cout << "  STATUS: FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Inserindo malha direcionada de arcos...\n";
    try {
        gOrientado.inserirAresta("0", "1", 1);
        gOrientado.inserirAresta("1", "2", 2);
        gOrientado.inserirAresta("2", "0", 3);
        gOrientado.inserirAresta("2", "3", 1);
        gOrientado.inserirAresta("3", "4", 2);
        gOrientado.inserirAresta("4", "5", 3);
        gOrientado.inserirAresta("5", "3", 4);
        cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        cout << "  STATUS: FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Verificar existencia da aresta direcionada existente (0, 1):\n";
    cout << "  Saida Esperada: VERDADEIRO\n";
    try {
        bool obtido = gOrientado.verificarAresta("0", "1");
        cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (obtido) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Verificar existencia na direcao inversa (1, 0):\n";
    cout << "  Saida Esperada: FALSO\n";
    try {
        bool obtido = gOrientado.verificarAresta("1", "0");
        cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (!obtido) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Verificar Adjacencia Unidirecional (2, 3) vs (3, 2):\n";
    cout << "  Saida Esperada: (2,3)=VERDADEIRO e (3,2)=FALSO\n";
    try {
        bool dir1 = gOrientado.saoAdjacentes("2", "3");
        bool dir2 = gOrientado.saoAdjacentes("3", "2");
        cout << "  Saida Obtida:   (2,3): " << (dir1 ? "VERDADEIRO" : "FALSO")
             << " | (3,2): " << (dir2 ? "VERDADEIRO" : "FALSO") << "\n";
        if (dir1 && !dir2) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Remover arco direcionado (4, 5):\n";
    cout << "  Saida Esperada: FALSO para (4,5)\n";
    try {
        gOrientado.removerAresta("4", "5");
        bool aindaExiste = gOrientado.verificarAresta("4", "5");
        cout << "  Saida Obtida:   Arco (4,5) ainda existe? " << (aindaExiste ? "VERDADEIRO" : "FALSO") << "\n";
        if (!aindaExiste) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Remover vertice 3:\n";
    cout << "  Saida Esperada: FALSO para arcos de entrada e saida\n";
    try {
        gOrientado.removerVertice("3");
        bool adj23 = gOrientado.saoAdjacentes("2", "3");
        bool adj53 = gOrientado.saoAdjacentes("5", "3");
        cout << "  Saida Obtida:   Adjacencia (2,3)? " << (adj23 ? "VERDADEIRO" : "FALSO") << "\n";
        cout << "                  Adjacencia (5,3)? " << (adj53 ? "VERDADEIRO" : "FALSO") << "\n";
        if (!adj23 && !adj53) {
            cout << "  STATUS:         PASSOU\n\n";
            passou++;
        } else {
            cout << "  STATUS:         FALHOU\n\n";
            falhou++;
        }
    } catch (...) {
        cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    cout << "[TESTE] Exibir estado impresso dos grafos finais:\n";
    cout << "--------------------------------------------------\n";
    try {
        cout << ">> GRAFO NAO ORIENTADO RESULTANTE:\n";
        gNaoOrientado.exibirGrafo();

        cout << "\n>> GRAFO ORIENTADO RESULTANTE:\n";
        gOrientado.exibirGrafo();

        cout << "--------------------------------------------------\n";
        cout << "  STATUS:         PASSOU\n\n";
        passou++;
    } catch (...) {
        cout << "--------------------------------------------------\n";
        cout << "  STATUS:         FALHOU \n\n";
        excecoes++;
    }

    // Ordenação topológica do grafo orientado (se aplicável)
    try {
        cout << "\n>> ORDENACAO TOPOLOGICA (GRAFO NAO ORIENTADO):\n";
        auto topoNao = gNaoOrientado.ordenacaoTopologica();
        cout << "  Resultado: [";
        for (size_t i = 0; i < topoNao.size(); ++i) {
            cout << topoNao[i] << (i + 1 == topoNao.size() ? "" : ", ");
        }
        cout << "]\n";
    } catch (...) {
        cout << "  Falha ao calcular ordenacao topologica (comum em grafos nao orientados)\n";
    }

    try {
        cout << "\n>> ORDENACAO TOPOLOGICA (GRAFO ORIENTADO):\n";
        auto topoSim = gOrientado.ordenacaoTopologica();
        cout << "  Resultado: [";
        for (size_t i = 0; i < topoSim.size(); ++i) {
            cout << topoSim[i] << (i + 1 == topoSim.size() ? "" : ", ");
        }
        cout << "]\n";
    } catch (...) {
        cout << "  Falha ao calcular ordenacao topologica\n";
    }

    cout << "==================================================\n";
    cout << "         RESUMO FINAL DA BATERIA DE TESTES        \n";
    cout << "==================================================\n";
    cout << "  TESTES QUE PASSARAM: " << passou << "\n";
    cout << "  TESTES QUE FALHARAM: " << falhou << "\n";
    cout << "  EXCECOES CAPTURADAS: " << excecoes << "\n";
    cout << "  TOTAL DE CASOS TESTADOS: " << (passou + falhou + excecoes) << "\n";
    cout << "==================================================\n";
}
