#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <map>
#include <queue>

using namespace std;

struct Edge {
    string source;
    string destination;
    int capacity;
    int flow;
};
class Graph{
    private:
        unordered_map<string, vector<string>> grafo_guloso;
        unordered_map<string, vector<Edge>> grafo_exato;
        unordered_set<string> visitedNodes;
        int cont;

    public:
        int get_count(){
            return cont;
        }

        Graph();
        // Função para adicionar uma aresta em um mapa de adjacência
        void addEdge_guloso(const string& node, const string& edge);
        // Função para executar a DFS no grafo
        void Guloso(const string& startNode);
        int Exato(const string& source, const string& sink);
        void addEdge_exato(const string& source, const string& destination);
        bool bfs(const unordered_map<string, vector<Edge>>& grafo_residual, const string& source, const string& destination, unordered_map<string, string>& parent);
};

#endif