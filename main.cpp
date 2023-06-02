#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "graph.hpp"

#define INF 0x3f3f3f3f

using namespace std;

void retirar_elementos_repetidos(vector<string>& vetor);

int main(int argc, char const *argv[]) {

    auto start = std::chrono::high_resolution_clock::now(); // Obter o horário de início

    int num_usuarios, num_ofertas_emprego, num_qualificações;
    string usuario, vaga;
    vector<string> usuarios;
    Graph grafo;

    cin >> num_usuarios >> num_ofertas_emprego >> num_qualificações; 

    string source = "source";
    string sink = "sink";
    grafo.addVertex(source);
    grafo.addVertex(sink);
    for(int i=0 ; i<num_qualificações ; i++){
        cin >> usuario >> vaga;
        usuarios.push_back(usuario);
        grafo.addEdge_guloso(usuario,vaga);
        grafo.addVertex(usuario);
        grafo.addVertex(vaga);
        grafo.addEdge(usuario,vaga);
        grafo.addEdge(vaga, sink);
        grafo.addEdge(source, usuario);
    }

    retirar_elementos_repetidos(usuarios);

    for(int i=0 ; i<num_usuarios ; i++){
        grafo.Guloso(usuarios[i]);
        //grafo.addEdge(source, usuarios[i]);
    }

   
    cout << grafo.fordFulkerson() << endl;

    cout << "Guloso: " << grafo.get_count() << endl;

    auto end = std::chrono::high_resolution_clock::now(); // Obter o horário de término

    // Calcular a duração em segundos
    std::chrono::duration<double> duration = end - start;
    double seconds = duration.count();
    cout << "Tempo de execução: " << seconds << " segundos" << endl;

    return 0;
}

void retirar_elementos_repetidos(vector<string>& vetor){
    sort(vetor.begin(), vetor.end());
    auto fim = unique(vetor.begin(), vetor.end());
    vetor.resize(distance(vetor.begin(), fim));
}