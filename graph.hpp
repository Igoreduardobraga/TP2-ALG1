#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <chrono>
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
    int source;
    int destination;
    int capacity;
    int flow;
};

class Graph{
    private:
        unordered_map<string, vector<string>> grafo_guloso;
        unordered_set<string> visitedNodes;
        unordered_map<string, int> tabela;
        vector<vector<Edge>> adj_list;
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
        void addVertex(const string& vertex);
        void addEdge(const string& source, const string& destination);
        bool bfs(int source, int sink, vector<int>& parent);
        int fordFulkerson();
};

#endif