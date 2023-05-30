#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.hpp"

#define INF 0x3f3f3f3f

using namespace std;

int main(int argc, char const *argv[]) {
    
    int num_usuarios, num_ofertas_emprego, num_qualificações;
    string usuario, vaga;
    vector<string> usuarios;
    Graph grafo;

    cin >> num_usuarios >> num_ofertas_emprego >> num_qualificações; 

    for(int i=0 ; i<num_qualificações ; i++){
        cin >> usuario >> vaga;
        usuarios.push_back(usuario);
        grafo.addEdge(usuario,vaga);
    }

    sort(usuarios.begin(), usuarios.end());

    // Passo 2: Remover elementos duplicados consecutivos
    auto novoFim = std::unique(usuarios.begin(), usuarios.end());

    // Passo 3: Redimensionar o usuarios
    usuarios.resize(std::distance(usuarios.begin(), novoFim));

    for(int i=0 ; i<num_usuarios ; i++){
        grafo.dfs(usuarios[i]);
    }

    cout << "Guloso: " << grafo.get_count() << endl;

    return 0;
}