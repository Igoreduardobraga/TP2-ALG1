#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.hpp"

#define INF 0x3f3f3f3f

using namespace std;

void retirar_elementos_repetidos(vector<string>& vetor);

int main(int argc, char const *argv[]) {
    
    int num_usuarios, num_ofertas_emprego, num_qualificações;
    string usuario, vaga;
    vector<string> usuarios;
    vector<string> vagas;
    Graph grafo;

    cin >> num_usuarios >> num_ofertas_emprego >> num_qualificações; 

    for(int i=0 ; i<num_qualificações ; i++){
        cin >> usuario >> vaga;
        usuarios.push_back(usuario);
        vagas.push_back(vaga);
        grafo.addEdge_guloso(usuario,vaga);
        grafo.addEdge_exato(usuario,vaga);
    }

    retirar_elementos_repetidos(usuarios);
    retirar_elementos_repetidos(vagas);

    string source = "source";
    string sink = "sink";
    for(int i=0 ; i<num_usuarios ; i++){
        grafo.Guloso(usuarios[i]);
        grafo.addEdge_exato(source, usuarios[i]);
    }

    for(int i=0 ; i<num_ofertas_emprego ; i++){
        grafo.addEdge_exato(vagas[i], sink);
    }

    cout << grafo.Exato(source, sink) << endl;

    //cout << "Guloso: " << grafo.get_count() << endl;

    return 0;
}

void retirar_elementos_repetidos(vector<string>& vetor){
    sort(vetor.begin(), vetor.end());
    auto fim = unique(vetor.begin(), vetor.end());
    vetor.resize(distance(vetor.begin(), fim));
}