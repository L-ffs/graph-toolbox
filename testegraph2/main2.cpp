#include "../headders/Graph.h"
#include "../headders/GraphReader.h"
#include <vector>
using namespace std;

int main () {

    GraphReader leitor;
    Graph *graph= leitor.readGraphFile("GraphFile_Model.graph");
    vector<int> ordenada = graph->topologicalSort();

    cout << "seczo";
    for (auto i : ordenada) {
        cout << "->" << i << "\n";
    }
    
    return 0;
} 