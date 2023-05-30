#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Node {
public:
    string name;
    vector<Node*> neighbors;

    Node(string name) : name(name) {}
};

class Graph {
public:
    unordered_map<string, Node*> nodes;

    void addNode(string name) {
        if (nodes.find(name) == nodes.end()) {
            Node* newNode = new Node(name);
            nodes[name] = newNode;
        }
    }

    void addEdge(string from, string to) {
        addNode(from);
        addNode(to);

        Node* fromNode = nodes[from];
        Node* toNode = nodes[to];

        fromNode->neighbors.push_back(toNode);
    }

    void dfs(Node* node, unordered_set<Node*>& visited) {
        visited.insert(node);
        cout << node->name << " ";

        for (Node* neighbor : node->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, visited);
            }
        }
    }

    void dfsTraversal(string startNodeName) {
        unordered_set<Node*> visited;
        Node* startNode = nodes[startNodeName];

        cout << "DFS Traversal starting from " << startNodeName << ":" << endl;
        dfs(startNode, visited);
        cout << endl;
    }
};

int main() {
    Graph graph;

    graph.addEdge("Andre", "CFO");
    graph.addEdge("Bruno", "RED");
    graph.addEdge("Bruno", "SWE");
    graph.addEdge("Maria", "CEO");
    graph.addEdge("Maria", "CFO");
    graph.addEdge("Maria", "CTO");
    graph.addEdge("Paulo", "CFO");
    graph.addEdge("Paulo", "CTO");
    graph.addEdge("Pedro", "RED");

    graph.dfsTraversal("Maria");

    return 0;
}